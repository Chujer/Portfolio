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
    for (Object* tile : sampleTile)
        delete tile;
    for (Object* tile : tileMap)
        delete tile;
}

void MapEditerScene::Update()
{
 /*   for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        quad.second->Update();
    }*/
}

void MapEditerScene::Render()
{
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        quad.second->Render();
    }
}

void MapEditerScene::PostRender()
{
    const char* list[] = { "BG", "OBJ" };
    ImGui::ListBox("Type", (int*)&selectType, list, 2);

   /* Save();
    Load();*/
}


void MapEditerScene::CreateSample()
{
    UINT width = 3;
    Vector2 size = sampleTileSize;
    Vector2 startPos(WIN_WIDTH - size.x, WIN_HEIGHT - size.y);
    int count = 0;

    for (pair<string, ObjectSample::InstanceData> data : ObjectSample::Get()->GetSampleData())
    {
        UINT index = count;
        Vector2 pos(index % width, index / width);
        Object* object = new Object(data.first);
        object->Position() = startPos - (pos * size);
        object->UpdateTransform();

        instanceQuads[data.first] = new InstanceQuad(data.first);
        instanceQuads[data.first]->AddPushDatas(object);
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
