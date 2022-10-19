#pragma once

class InstanceQuad
{
private:
    struct InstanceData
    {
        Matrix transform;
        Vector2 maxFrame;
        Vector2 curFrame;
    };
public:
    InstanceQuad(ObjectSample::InstanceData data);
    ~InstanceQuad();

    void AddPushDatas(Object* object);

    void Update();
    void Render();

private:
    void CreateInstanceBuffer();


private:

    vector<Object*> objectDatas;
    vector<InstanceData> instanceDatas;
    Quad* quad;
    VertexBuffer* instanceBuffer;

};