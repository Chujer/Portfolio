#include "Framework.h"

BabaTileMap::BabaTileMap(UINT width, UINT height)
	:width(width), height(height)
{
	ObjectSample::Get();
	CreateTile();
    


}

BabaTileMap::~BabaTileMap()
{
  
    for (Object* tile : tiles)
        delete tile;
    for (Object* tile : bgTiles)
        delete tile;
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        delete quad.second;
    }
}

void BabaTileMap::Update()
{
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        quad.second->Update();
    }
}

void BabaTileMap::Render()
{
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        quad.second->Render();
    }

    for (Object* tile : tiles)
    {
        if (tile->effect == "MOVE")
            OneMoreRender(tile->tag);
    }
    for (pair<string, InstanceQuad*> quad : instanceQuads)
    {
        quad.second->ParticleRender();
    }
}

void BabaTileMap::OneMoreRender(string key)
{
    instanceQuads[key]->Render();
}

void BabaTileMap::SetBufferSize(string key, int count)
{
    instanceQuads[key]->SetBufferSize(count);
}

void BabaTileMap::ClickTile(Object* selectSample)       // 선택한 타일을 기존BG타일 위치에 생성
{   
    DeleteObjTile();
    if (KEY_PRESS(VK_LBUTTON))
    {
        for (Object* bgTile : bgTiles)
        {
            if (bgTile->GetCollider()->IsPointCollision(mousePos))
            {
                Object* object = new Object(selectSample->tag);
                object->Position() = bgTile->Position();
                object->SetParent(this);
                object->UpdateTransform();
                tiles.push_back(object);
                if (instanceQuads.count(object->tag) == 0)
                    instanceQuads[object->tag] = new InstanceQuad(object->tag);
                instanceQuads[object->tag]->AddPushDatas(object);

                for (Object* tile : instanceQuads[object->tag]->GetObjects())
                {
                    tile->GetInstanceData().curFrame.y = 0;
                    tile->AnimTime() = 0;
                }
                return;
            }
        }
    }
}

void BabaTileMap::DeleteObjTile()
{
    if (KEY_PRESS(VK_LBUTTON))
    {
        vector<Object*>::iterator iter = tiles.begin();

        for (; iter != tiles.end(); )
        {
            if ((*iter)->GetCollider()->IsPointCollision(mousePos))
            {
                instanceQuads[(*iter)->tag]->DeleteObject(*iter);
                iter = tiles.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
    if (KEY_PRESS(VK_RBUTTON))
    {
        vector<Object*>::iterator iter = tiles.begin();

        for (; iter != tiles.end(); )
        {
            if ((*iter)->GetCollider()->IsPointCollision(mousePos))
            {
                instanceQuads[(*iter)->tag]->DeleteObject(*iter);
                iter = tiles.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
}

void BabaTileMap::SetColliderOff()
{

    for (Object* tile : tiles)
        tile->GetCollider()->SetActive(false);
    for (Object* tile : bgTiles)
        tile->GetCollider()->SetActive(false);
}

void BabaTileMap::Save(string file)
{
    BinaryWriter* writer = new BinaryWriter(file);

    writer->UInt(width);
    writer->UInt(height);

    writer->UInt(bgTiles.size());

    for (Object* tile : bgTiles)
    {
        BabaTileMap::Data data;
        data.key = tile->tag;
        data.pos = tile->Position();

        writer->String(data.key);
        writer->Float(data.pos.x);
        writer->Float(data.pos.y);
    }

    writer->UInt(tiles.size());

    for (Object* tile : tiles)
    {
        BabaTileMap::Data data;
        data.key = tile->tag;
        data.pos = tile->Position();

        writer->String(data.key);
        writer->Float(data.pos.x);
        writer->Float(data.pos.y);
    }

    delete writer;
}

void BabaTileMap::Load(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    width = reader->UInt();
    height = reader->UInt();

    UINT size = reader->UInt();

    ClearBGTile();
    SetMapPosition();
    bgTiles.resize(size);

    for (Object*& tile : bgTiles)
    {
        BabaTileMap::Data data;
        data.key = reader->String();
        data.pos.x = reader->Float();
        data.pos.y = reader->Float();

        tile = new Object(data.key);
        tile->Position() = data.pos;
        tile->SetParent(this);
        tile->UpdateTransform();
        
        if (instanceQuads.count(tile->tag) == 0)
            instanceQuads[tile->tag] = new InstanceQuad(tile->tag,width*height);
        instanceQuads[tile->tag]->AddPushDatas(tile);
    }

    size = reader->UInt();

    ClearOBJTile();
    tiles.resize(size);

    for (Object*& tile : tiles)
    {
        BabaTileMap::Data data;
        data.key = reader->String();
        data.pos.x = reader->Float();
        data.pos.y = reader->Float();

        tile = new Object(data.key);
        if (tile->tag.find("IS"))
        {
            Object* temp = tile;
            tile = new IsObject(tile->tag);
            delete temp;
        }
        tile->Position() = data.pos;
        tile->SetParent(this);
        tile->UpdateTransform();

        if (instanceQuads.count(tile->tag) == 0)
            instanceQuads[tile->tag] = new InstanceQuad(tile->tag);
        instanceQuads[tile->tag]->AddPushDatas(tile);
    }

    delete reader;
}

void BabaTileMap::CreateTile()
{
    tileSize = {48,48 };

    for (UINT y = 0; y < height; y++)
    {
        for (UINT x = 0; x < width; x++)
        {
            Object* object = new Object("ABG");
            object->Position() = Vector2(tileSize.x * x, tileSize.y * y);

            object->SetParent(this);
            object->UpdateTransform();
            bgTiles.push_back(object);
            if(instanceQuads.count("ABG")==0)
               instanceQuads["ABG"] = new InstanceQuad("ABG",height*width);
            instanceQuads["ABG"]->AddPushDatas(object);
        }
    }

    SetMapPosition();
}

void BabaTileMap::ClearBGTile()
{
    for (Object* tile : bgTiles)
        instanceQuads[tile->tag]->DeleteObject(tile);

    bgTiles.clear();
}

void BabaTileMap::ClearOBJTile()
{
    for (Object* tile : tiles)
        instanceQuads[tile->tag]->DeleteObject(tile);

    tiles.clear();
}

void BabaTileMap::SetMapPosition()
{
    if (width % 2 == 0)
        position.x = CENTER_X - (TILE_SIZE.x / 2) - (((width / 2) - 1) * TILE_SIZE.x);
    if (height % 2 == 0)
        position.y = CENTER_Y - (TILE_SIZE.y / 2) - (((height / 2) - 1) * TILE_SIZE.y);
    if (width % 2 != 0)
        position.x = CENTER_X - ((width / 2) * TILE_SIZE.x);
    if (height % 2 != 0)
        position.y = CENTER_Y - ((height / 2) * TILE_SIZE.y);

    Position() = position;
    UpdateWorld();
}
