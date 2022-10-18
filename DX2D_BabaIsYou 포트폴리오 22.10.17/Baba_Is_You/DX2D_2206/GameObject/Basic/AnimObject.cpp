#include "Framework.h"

AnimObject::AnimObject()
{
    vertexShader = Shader::AddVS(L"Shaders/VertexUV.hlsl");
    pixelShader = Shader::AddPS(L"Shaders/PixelUV.hlsl");

    worldBuffer = new MatrixBuffer();
    colorBuffer = new ColorBuffer();
}

AnimObject::~AnimObject()
{
    for (pair<int, Clip *> clip : clips)
        delete clip.second;

    delete worldBuffer;
    delete colorBuffer;
}

void AnimObject::Update()
{    
    if (curClip == nullptr) return;

    curClip->Update();
    UpdateWorld();
}

void AnimObject::Render()
{
    if (curClip == nullptr) return;

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);
    colorBuffer->SetPS(0);

    vertexShader->Set();
    pixelShader->Set();

    curClip->Render();
}

void AnimObject::InstancingRender()
{
}

void AnimObject::SetIntancingShaders()
{
    vertexShader = Shader::AddVS(L"Shaders/VertexInstancing.hlsl");
    pixelShader = Shader::AddPS(L"Shaders/PixelInstancing.hlsl");
}

void AnimObject::SetColor(float r, float g, float b, float a)
{
    colorBuffer->Set(r, g, b, a);
}

void AnimObject::SetPixelShader(wstring file)
{
    pixelShader = Shader::AddPS(file);
}
