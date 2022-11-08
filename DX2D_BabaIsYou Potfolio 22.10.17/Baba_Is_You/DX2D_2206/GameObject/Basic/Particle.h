#pragma once

class Particle
{
    friend class ParticleManager;
private:
    struct InstanceData
    {
        Matrix transform;
        Vector2 maxFrame = { 1, 1 };
        Vector2 curFrame = { 1, 1 };
    };

    struct FluidParticleData
    {
        bool isFluidParticle = false;
        Vector2 Scale = { 1,1 };
        float Time = 0.0f;
    };

    struct ParticleData
    {
        UINT count = 100;
        float duration = 1.0f;
        Vector2 minVelocity = { -1, -1 };
        Vector2 maxVelocity = { 1 , 1 };
        Vector2 minAccelation = { 0, 0 };
        Vector2 maxAccelation = { 0, 0 };
        float minSpeed = 1.0f;
        float maxSpeed = 100.0f;
        float minAngularVelocity = -10.0f;
        float maxAngularVelocity = 10.0f;
        float minStartTime = 0.0f;
        float maxStartTime = 0.0f;
        Vector2 Scale = { 1, 1 };
        Float4 startColor = { 1, 1, 1, 1 };
        Float4 endColor = { 1, 1 ,1, 1 };
        FluidParticleData fluidData;
    };

    struct ParticleInfo
    {
        Vector2 velocity;
        Vector2 accelation;
        Vector2 scale;
        float speed;
        float angularVelocity;
        float startTime;
        FluidParticleData fluidData;
    };

    struct ParticleInstanceData
    {
        vector<InstanceData*> instances;
        VertexBuffer* instanceBuffer;

    };
public:
    Particle(string file);
    ~Particle();

    void Update();
    void Render();

    void Play(Vector2 pos);
    void Stop();
    void SetCustomColor(Float4 color);

    bool GetIsPlay() { return isPlay; }
    void SetRotate(bool isRotate) { this->isRotate = isRotate; }
    Quad* GetQuad() { return quad; }

    string GetPath() { return path; }

    ParticleInstanceData GetParticleInstanceData()
    {
        particleInstanceData.instances.clear();
        for (InstanceData instanceData : instances)
        {
            particleInstanceData.instances.push_back(&instanceData);
        }
        return particleInstanceData;
    }
    
private:
    void LoadData(string file);
    void UpdateParticleInfo();

private:
    string path;
    bool isPlay = false;

    Quad* quad;
    vector<InstanceData> instances;
    vector<ParticleInfo> particleInfos;
    vector<Transform> transforms;

    VertexBuffer* instanceBuffer;

    ParticleData data;
    ParticleInstanceData particleInstanceData;

    float lifeTime = 0.0f;
    Float4 color;
    Float4 customColor;
    bool isCustomColor = false;
    bool isRotate = false;
};