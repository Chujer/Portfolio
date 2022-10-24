#include "Framework.h"
#include "MapEditerScene.h"

MapEditerScene::MapEditerScene()
{
    backGround = new Quad(L"Textures/BackGround.png");
    backGround->Position() = { CENTER_X,CENTER_Y };
    backGround->UpdateWorld();

	ObjectSample::Get();
    
    CreateSample();

    char path[128];
    GetCurrentDirectoryA(sizeof(path), path);
    projectPath = path;
	
}

MapEditerScene::~MapEditerScene()
{
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        delete quad.second;
    }
    delete tileMap;
    delete backGround;
}

void MapEditerScene::Update()
{
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        quad.second->Update();
    }

    if(tileMap != nullptr)
       tileMap->Update();

    ClickSampleBtn();

    if (selectTile != nullptr)
    {
        selectTile->Position() = mousePos;
        if(tileMap != nullptr)
            tileMap->ClickTile(selectTile);
    }
}

void MapEditerScene::Render()
{
    backGround->Render();

    if (tileMap != nullptr)
        tileMap->Render();

    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        quad.second->Render();
    }
}

void MapEditerScene::PostRender()
{
    ImGui::Text("Tile");
    for (pair<string, bool> check : checkTiles)
    {
        if (ImGui::Checkbox(check.first.c_str(), &checkTiles[check.first]))
        {
            check.second = checkTiles[check.first];
            for (pair<string, vector<Object*>> tile : sampleTile)
            {
                if (tile.first.find(check.first) != string::npos)
                {
                    for (Object*& t : sampleTile[tile.first])
                    {
                        t->SetActive(check.second);
                        SortSample();
                    }
                }
            }
        }
    }

    ImGui::Text("TileSize");
    ImGui::InputInt2("Size", size);
    if (ImGui::Button("Create"))
    {
        if (size[0] == 0 && size[1] == 0)
        {
            delete tileMap;
            tileMap = nullptr;
            return;
        }
        if (tileMap != nullptr)
            delete tileMap;
        tileMap = new BabaTileMap(size[0], size[1]);
        tileMap->SetBufferSize("ABG", size[0] * size[1]);
       // tileMap->Position() = { 80,80 };
        tileMap->UpdateWorld();
    }

    ImGui::Text("");
    Save();
    Load();
}

void MapEditerScene::ClickSampleBtn()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        for (pair<string, vector<Object*>> tiles : sampleTile)
        {
            for (Object* tile : tiles.second)
            {
                if (!tile->Active())
                    continue;

                if (tile->GetCollider()->IsPointCollision(mousePos))
                {
                    if (selectTile != nullptr)
                    {
                        if (selectTile->tag.find("PROPERTY") != string::npos)
                            instanceQuads[selectTile->tag]->DeleteObject(selectTile);
                        else if (selectTile->tag.find("NAME") == string::npos)
                            instanceQuads[selectTile->tag.substr(0, selectTile->tag.find('_'))]->DeleteObject(selectTile);
                        else
                            instanceQuads[selectTile->tag]->DeleteObject(selectTile);
                    }

                    selectTile = new Object(tile->tag);
                    selectTile->Position() = mousePos;
                    selectTile->UpdateTransform();
                    

                    if(selectTile->tag.find("PROPERTY") != string::npos)
                        instanceQuads[selectTile->tag]->AddPushDatas(selectTile);
                    else if(selectTile->tag.find("NAME") == string::npos)
                        instanceQuads[selectTile->tag.substr(0, selectTile->tag.find('_'))]->AddPushDatas(selectTile);
                    else
                        instanceQuads[selectTile->tag]->AddPushDatas(selectTile);


                }
            }
        }
    }
}


void MapEditerScene::CreateSample()
{
    UINT width = 6;
    Vector2 size = sampleTileSize;
    Vector2 startPos(WIN_WIDTH - size.x, WIN_HEIGHT - (size.y * 3));
    int count = 0;
    
    

    for (pair<string, ObjectSample::InstanceData> data : ObjectSample::Get()->GetSampleData())
    {
        UINT index = count;
        Vector2 pos(index % width, index / width);
        Object* object = new Object(data.first);
        object->Position() = startPos - (pos * size);
        object->SetActive(false);
        object->UpdateTransform();
        object->AnimPlay() = false;
        

        if (data.first.find("PROPERTY") != string::npos)
        {
            if (instanceQuads.count(data.first) == 0)
                instanceQuads[data.first] = new InstanceQuad(data.first);

            instanceQuads[data.first]->AddPushDatas(object);
            sampleTile[data.first].push_back(object);
        }
        else if (data.first.find("NAME") != string::npos)
        {
            instanceQuads[data.first] = new InstanceQuad(data.first);
            instanceQuads[data.first]->AddPushDatas(object);
            sampleTile[data.first].push_back(object);
        }
        else
        {
            if (instanceQuads.count(data.first.substr(0, data.first.find('_'))) == 0)
                instanceQuads[data.first.substr(0, data.first.find('_'))] = new InstanceQuad(data.first);

            instanceQuads[data.first.substr(0, data.first.find('_'))]->AddPushDatas(object);
            sampleTile[data.first.substr(0, data.first.find('_'))].push_back(object);
        }
        checkTiles[data.first.substr(0, data.first.find('_'))] = false;
        count++;
    }

}

void MapEditerScene::SortSample()
{
    INT width = 6;
    Vector2 size = sampleTileSize;
    Vector2 startPos(WIN_WIDTH - (size.x * width), WIN_HEIGHT - (size.y * 3));
    UINT index = 0;

    for (pair<string, vector<Object*>> tile : sampleTile)
    {
        for (Object* t : tile.second)
        {
            if (t->Active() == true)
            {
                Vector2 pos(index % width, index / width);
                t->Position().x = startPos.x + (pos.x * size.x);
                t->Position().y = startPos.y - (pos.y * size.y);
                index++;
            }
        }
    }
}

void MapEditerScene::Save()
{
    if (ImGui::Button("Save"))
        ImGuiFileDialog::Instance()->OpenDialog("Save", "SaveFile", ".map", ".");

    if (ImGuiFileDialog::Instance()->Display("Save"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();
            file = file.substr(projectPath.size() + 1, file.length());

            tileMap->Save(file);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void MapEditerScene::Load()
{
    if (ImGui::Button("Load"))
        ImGuiFileDialog::Instance()->OpenDialog("Load", "LoadFile", ".map", ".");

    if (ImGuiFileDialog::Instance()->Display("Load"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();
            file = file.substr(projectPath.size() + 1, file.length());

            if (tileMap == nullptr)
                tileMap = new BabaTileMap(0, 0);

            tileMap->Load(file);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}
