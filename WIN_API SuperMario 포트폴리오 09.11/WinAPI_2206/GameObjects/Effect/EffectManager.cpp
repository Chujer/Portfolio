#include "Framework.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
    for (pair<string, Effects> effects : totalEffect)
    {
        for (Effect * effect : effects.second)
            delete effect;

        effects.second.clear();
    }

    totalEffect.clear();
}

void EffectManager::Update()
{
    for (pair<string, Effects> effects : totalEffect)
    {
        for (Effect * effect : effects.second)
            effect->Update();
    }
}

void EffectManager::Render(HDC hdc)
{
    for (pair<string, Effects> effects : totalEffect)
    {
        for (Effect * effect : effects.second)
            effect->Render(hdc);
    }
}

void EffectManager::Add(string key, Texture * texture, UINT poolingCount, float frameUpdateTime)
{
    if (totalEffect.count(key) > 0) return;

    Effects effects(poolingCount);

    for (Effect *& effect : effects)
    {
        effect = new Effect(texture, frameUpdateTime);
    }

    totalEffect[key] = effects;
}

void EffectManager::Play(string key, Vector2 pos)
{
    if (totalEffect.count(key) == 0) return;

    for (Effect * effect : totalEffect[key])
    {
        if (!effect->Active())
        {
            effect->Play(pos);
            return;
        }
    }
}
