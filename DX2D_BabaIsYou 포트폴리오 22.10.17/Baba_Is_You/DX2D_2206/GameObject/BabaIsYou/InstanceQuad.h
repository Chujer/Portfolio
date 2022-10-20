#pragma once

class InstanceQuad
{
private:
    const UINT DESC_SIZE = 100;

    struct InstanceData
    {
        Matrix transform;
        Vector2 maxFrame;
        Vector2 curFrame;
    };
public:
    InstanceQuad(string key);
    ~InstanceQuad();

    void AddPushDatas(Object* object);

    void Update();
    void Render();

    void SetPixelShader(wstring path)
    {
        quad->SetPixelShader(path);
    }

private:
    void CreateInstanceBuffer();


private:

    vector<Object*> objectDatas;
    vector<InstanceData> instanceDatas;
    Quad* quad;
    VertexBuffer* instanceBuffer;

};