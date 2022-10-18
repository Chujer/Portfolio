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
	Quad* quad;
    InstanceData instanceData;
    VertexBuffer* instanceBuffer;
};