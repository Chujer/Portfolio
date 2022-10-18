#include "Framework.h"

TileMap::TileMap(UINT width, UINT height)
    : width(width), height(height)
{
    CreateTile();
}

TileMap::~TileMap()
{
    for (Tile * tile : bgTiles)
        delete tile;

    for (Tile * tile : objTiles)
        delete tile;
}

void TileMap::Update()
{
    for (Tile * tile : bgTiles)
        tile->Update();

    for (Tile * tile : objTiles)
        tile->Update();

    UpdateWorld();
}

void TileMap::Render()
{
    for (Tile * tile : bgTiles)
        tile->Render();

    for (Tile * tile : objTiles)
        tile->Render();
}

void TileMap::ClickTile(Quad * selectSample, Tile::Type type)
{
    switch (type)
    {
    case Tile::BG:
        SetBGTile(selectSample->GetFile(), selectSample->Rotation().z);
        break;
    case Tile::OBJ:
        SetOBJTile(selectSample->GetFile(), selectSample->Rotation().z);
        break;    
    }
}

void TileMap::DeleteObjTile()
{
    //for (UINT i = 0; i < objTiles.size(); i++)
    //{
    //    if (objTiles[i]->GetCollider()->IsPointCollision(mousePos))
    //    {
    //        objTiles.erase(objTiles.begin() + i);
    //        return;
    //    }
    //}

    vector<Tile *>::iterator iter = objTiles.begin();

    for (; iter != objTiles.end(); )
    {
        if ((*iter)->GetCollider()->IsPointCollision(mousePos))
        {
            iter = objTiles.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void TileMap::CreateTile()
{
    wstring baseTile = L"Textures/Tile/grass.png";
    Texture * texture = Texture::Add(baseTile);

    tileSize = texture->GetSize();

    for (UINT y = 0; y < height; y++)
    {
        for (UINT x = 0; x < width; x++)
        {
            Tile::Data data;
            data.textureFile = baseTile;
            data.type = Tile::BG;
            data.pos = Vector2(tileSize.x * x, tileSize.y * y);

            Tile * tile = new Tile(data);
            tile->SetParent(this);
            bgTiles.push_back(tile);
        }
    }
}

void TileMap::SetBGTile(wstring file, float angle)
{
    for (Tile * tile : bgTiles)
    {
        if (tile->GetCollider()->IsPointCollision(mousePos))
        {
            tile->SetTexture(file);
            tile->SetAngle(angle);
        }
    }
}

void TileMap::SetOBJTile(wstring file, float angle)
{
    DeleteObjTile();

    for (Tile * tile : bgTiles)
    {
        if (tile->GetCollider()->IsPointCollision(mousePos))
        {
            Tile::Data data = tile->GetData();
            data.angle = angle;
            data.textureFile = file;
            data.type = Tile::OBJ;

            Tile * tile = new Tile(data);
            tile->SetParent(this);
            tile->UpdateWorld();

            objTiles.push_back(tile);
            return;
        }
    }
}

void TileMap::Save(string file)
{
    BinaryWriter * writer = new BinaryWriter(file);

    writer->UInt(width);
    writer->UInt(height);

    writer->UInt(bgTiles.size());

    for (Tile * tile : bgTiles)
    {
        Tile::Data data = tile->GetData();

        writer->WString(data.textureFile);
        writer->Float(data.pos.x);
        writer->Float(data.pos.y);
        writer->Float(data.angle);
        writer->Int(data.type);
    }

    writer->UInt(objTiles.size());

    for (Tile * tile : objTiles)
    {
        Tile::Data data = tile->GetData();

        writer->WString(data.textureFile);
        writer->Float(data.pos.x);
        writer->Float(data.pos.y);
        writer->Float(data.angle);
        writer->Int(data.type);
    }

    delete writer;
}

void TileMap::Load(string file)
{
    BinaryReader * reader = new BinaryReader(file);

    width = reader->UInt();
    height = reader->UInt();

    UINT size = reader->UInt();

    ClearBGTile();
    bgTiles.resize(size);

    for (Tile *& tile : bgTiles)
    {
        Tile::Data data;
        data.textureFile = reader->WString();
        data.pos.x = reader->Float();
        data.pos.y = reader->Float();
        data.angle = reader->Float();
        data.type = (Tile::Type)reader->Int();

        tile = new Tile(data);
        tile->SetParent(this);
    }

    size = reader->UInt();

    ClearOBJTile();
    objTiles.resize(size);

    for (Tile *& tile : objTiles)
    {
        Tile::Data data;
        data.textureFile = reader->WString();
        data.pos.x = reader->Float();
        data.pos.y = reader->Float();
        data.angle = reader->Float();
        data.type = (Tile::Type)reader->Int();

        tile = new Tile(data);
        tile->SetParent(this);
    }

    delete reader;
}

void TileMap::ClearBGTile()
{
    for (Tile * tile : bgTiles)
        delete tile;

    bgTiles.clear();
}

void TileMap::ClearOBJTile()
{
    for (Tile * tile : objTiles)
        delete tile;

    objTiles.clear();
}
