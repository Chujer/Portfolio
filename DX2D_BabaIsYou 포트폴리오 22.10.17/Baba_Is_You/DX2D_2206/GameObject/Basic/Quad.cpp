#include "Framework.h"

Quad::Quad(wstring file, Vector2 startUV, Vector2 endUV, Vector2 pos)
    : startUV(startUV), endUV(endUV)
{
    texture = Texture::Add(file);

    size = (endUV - startUV) * texture->GetSize();

    float left = pos.x - size.x * 0.5f;
    float right = pos.x + size.x * 0.5f;
    float top = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    vertices.emplace_back(left, top, startUV.x, startUV.y);
    vertices.emplace_back(right, top, endUV.x, startUV.y);
    vertices.emplace_back(left, bottom, startUV.x, endUV.y);
    vertices.emplace_back(right, bottom, endUV.x, endUV.y);

    Init();    
}

Quad::Quad(Vector2 size, Vector2 pos)
{
    float left = pos.x - size.x * 0.5f;
    float right = pos.x + size.x * 0.5f;
    float top = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    this->size = size;

    vertices.emplace_back(left, top, 0, 0);
    vertices.emplace_back(right, top, 1, 0);
    vertices.emplace_back(left, bottom, 0, 1);
    vertices.emplace_back(right, bottom, 1, 1);
    
    Init();
}

Quad::~Quad()
{
    delete vertexBuffer;
    delete indexBuffer;
    delete worldBuffer;
    delete colorBuffer;
}

void Quad::Render()
{
    texture->PSSet();

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);
    colorBuffer->SetPS(0);

    vertexBuffer->Set();
    indexBuffer->Set();

    vertexShader->Set();
    pixelShader->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}

void Quad::SetRender()
{
    texture->PSSet();

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);
    colorBuffer->SetPS(0);

    vertexBuffer->Set();
    indexBuffer->Set();

    vertexShader->Set();
    pixelShader->Set();
}

void Quad::SetVertexShader(wstring file)
{
    vertexShader = Shader::AddVS(file);
}

void Quad::SetPixelShader(wstring file)
{
    pixelShader = Shader::AddPS(file);
}

void Quad::Resize(Vector2 size, Vector2 pos)
{
    float left = pos.x - size.x * 0.5f;
    float right = pos.x + size.x * 0.5f;
    float top = pos.y + size.y * 0.5f;
    float bottom = pos.y - size.y * 0.5f;

    vertices.clear();
    vertices.emplace_back(left, top, startUV.x, startUV.y);
    vertices.emplace_back(right, top, endUV.x, startUV.y);
    vertices.emplace_back(left, bottom, startUV.x, endUV.y);
    vertices.emplace_back(right, bottom, endUV.x, endUV.y);

    vertexBuffer->Update(vertices.data(), vertices.size());
}

void Quad::Init()
{
    vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
    pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");    

    vertexBuffer = new VertexBuffer(vertices.data(),
        sizeof(Vertex), vertices.size());

    indices = { 0, 1, 2, 2, 1, 3 };
    indexBuffer = new IndexBuffer(indices.data(), indices.size());

    worldBuffer = new MatrixBuffer();
    colorBuffer = new ColorBuffer();
}
