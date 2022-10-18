#pragma once

class Scene
{
public:
    Scene(int depth = 0) : depth(depth) {}
    virtual ~Scene() {}

    virtual void Update() = 0;

    virtual void PreRender() {};
    virtual void Render() = 0;
    virtual void PostRender() = 0;

    virtual void Start() {};
    virtual void End() {};

    int GetDepth() { return depth; }
    void SetDepth(int depth) { this->depth = depth; }

private:
    int depth;
};