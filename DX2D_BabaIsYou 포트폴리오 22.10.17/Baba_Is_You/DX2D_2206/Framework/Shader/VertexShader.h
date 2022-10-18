#pragma once

class VertexShader : public Shader
{
public:
    VertexShader(wstring file);
    ~VertexShader();

    virtual void Set() override;

private:
    void CreateInputLayout();

private:
    ID3D11VertexShader * vertexShader;
    ID3D11InputLayout * inputLayout;

    ID3D11ShaderReflection * reflection;
};