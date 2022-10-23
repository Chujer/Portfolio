#pragma once

class EffectManager : public Singleton<EffectManager>
{
public:
    EffectManager();
    ~EffectManager();

    void Update();
    void Render();

    void Add(string key, UINT poolCount, wstring textureFile,
        Vector2 maxFrame, float speed = 1.0f, bool isAdditive = false);

    void Play(string key, Vector2 pos);

private:
    typedef vector<Effect *> Effects;
    unordered_map<string, Effects> totalEffect;
};