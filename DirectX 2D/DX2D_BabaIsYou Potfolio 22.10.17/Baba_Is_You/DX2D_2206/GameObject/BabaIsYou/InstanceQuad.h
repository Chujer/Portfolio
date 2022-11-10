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
    InstanceQuad(string key,int count);
    ~InstanceQuad();

    void SetBufferSize(int count);

    void AddPushDatas(Object* object);

    void Update();
    void Render();
    void ParticleRender();

    void SetPixelShader(wstring path)
    {
        quad->SetPixelShader(path);
    }

    vector<Object*> GetObjects() { return objectDatas; }

    void DeleteObject(Object* object);

private:
    void CreateInstanceBuffer();
    void CreateInstanceBuffer(UINT maxCount);


private:

    vector<Object*> objectDatas;
    vector<InstanceData> instanceDatas;
    Quad* quad;
    VertexBuffer* instanceBuffer;

};