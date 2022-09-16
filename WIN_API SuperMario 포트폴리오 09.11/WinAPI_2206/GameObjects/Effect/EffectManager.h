#pragma once

class EffectManager : public Singleton<EffectManager>
{
public:
    EffectManager();
    ~EffectManager();

    void Update();
    void Render(HDC hdc);

    void Add(string key, Texture * texture, UINT poolingCount = 30, float frameUpdateTime = 0.1f);

    void Play(string key, Vector2 pos);

private:
    typedef vector<Effect *> Effects;

    map<string, Effects> totalEffect;
};