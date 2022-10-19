#pragma once

class TestScene : public Scene
{
private:
    struct InstanceData
    {
        Matrix transform;
        Vector2 maxFrame;
        Vector2 curFrame;
    };
public:
	TestScene();
	~TestScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

private:

    Object* objectData;
    Quad* quad;
    VertexBuffer* instanceBuffer;
    InstanceData instanceData;

	/*Quad* quad;
    InstanceData instanceData;
    VertexBuffer* instanceBuffer;
    int temp = 0;
    float time = 0;*/
};