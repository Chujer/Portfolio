#include "Framework.h"
#include "MapEditerScene.h"

MapEditerScene::MapEditerScene()
{
	ObjectSample::Get();

    CreateSample();
	
}

MapEditerScene::~MapEditerScene()
{
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        delete quad.second;
    }
    delete selectTile;

    for (Object* tile : tileMap)
        delete tile;
}

void MapEditerScene::Update()
{
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        if (checkTiles[quad.first] == false)
            continue;
        quad.second->Update();
    }
}

void MapEditerScene::Render()
{
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
       /* if (checkTiles[quad.first] == false)
            continue;*/
        if (checkTiles[quad.first] == false)
            continue;
        quad.second->Render();
    }
}

void MapEditerScene::PostRender()
{

    if (ImGui::Checkbox("NAME", &tempNameBool))
    {
        for (pair<string, bool> check : checkTiles)
        {
            if (check.first.find("NAME") != string::npos)
            {
                INT width = 6;
                Vector2 size = sampleTileSize;
                Vector2 startPos(WIN_WIDTH - size.x, WIN_HEIGHT - (size.y * 3));
                UINT index = 0;

                checkTiles[check.first] = tempNameBool;

                for (pair<string, vector<Object*>> tile : sampleTile)
                {
                    if (tile.first.find("NAME") == string::npos)
                    {
                        for (Object* t : tile.second)
                        {
                            if(t->Active())
                                index++;
                        }
                    }
                }
                for (pair<string, vector<Object*>> tile : sampleTile)
                {
                    if(tile.first.find("NAME") != string::npos)
                    {
                        tile.second.front()->SetActive(tempNameBool);
                        for (Object* t : tile.second)
                        {
                            Vector2 pos(index % width, index / width);
                            t->Position() = startPos - (pos * size);
                            index++;
                            t->SetActive(tempNameBool);
                        }
                    }
                }
            }
        }
    }
    for (pair<string, bool> check : checkTiles)
    {
        if (check.first.find("NAME") == string::npos)
        {
            if (ImGui::Checkbox(check.first.c_str(), &checkTiles[check.first]))
            {
                INT width = 6;
                Vector2 size = sampleTileSize;
                Vector2 startPos(WIN_WIDTH - size.x, WIN_HEIGHT - (size.y * 3));
                UINT index = 0;
                for (pair<string, vector<Object*>> tile : sampleTile)
                {
                    for (Object* t : tile.second)
                    {
                        if (t->Active())
                            index++;
                    }
                }
                for (Object* tile : sampleTile[check.first])
                {
                    Vector2 pos(index % width, index / width);
                    tile->Position() = startPos - (pos * size);
                    index++;
                    tile->SetActive(checkTiles[check.first]);
                }
            }
        }
    }
    const char* list[] = { "BG", "OBJ" };
    ImGui::ListBox("Type", (int*)&selectType, list, 2);

   /* Save();
    Load();*/
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
        

      //  sampleTile[data.first.substr(0, data.first.find('_'))].push_back(object);

        if (data.first.find("NAME") != string::npos)
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

//void MapEditerScene::Save()
//{
//    if (ImGui::Button("Save"))
//        ImGuiFileDialog::Instance()->OpenDialog("Save", "SaveFile", ".map", ".");
//
//    if (ImGuiFileDialog::Instance()->Display("Save"))
//    {
//        if (ImGuiFileDialog::Instance()->IsOk())
//        {
//            string file = ImGuiFileDialog::Instance()->GetFilePathName();
//            file = file.substr(projectPath.size() + 1, file.length());
//
//            tileMap->Save(file);
//        }
//
//        ImGuiFileDialog::Instance()->Close();
//    }
//}
//
//void MapEditerScene::Load()
//{
//    if (ImGui::Button("Load"))
//        ImGuiFileDialog::Instance()->OpenDialog("Load", "LoadFile", ".map", ".");
//
//    if (ImGuiFileDialog::Instance()->Display("Load"))
//    {
//        if (ImGuiFileDialog::Instance()->IsOk())
//        {
//            string file = ImGuiFileDialog::Instance()->GetFilePathName();
//            file = file.substr(projectPath.size() + 1, file.length());
//
//            tileMap->Load(file);
//        }
//
//        ImGuiFileDialog::Instance()->Close();
//    }
//}
