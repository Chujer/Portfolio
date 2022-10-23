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
    }
}

void EffectManager::Update()
{
    for (pair<string, Effects> effects : totalEffect)
    {
        for (Effect * effect : effects.second)
            effect->Update();
    }
}

void EffectManager::Render()
{
    for (pair<string, Effects> effects : totalEffect)
    {
        for (Effect * effect : effects.second)
            effect->Render();
    }
}

void EffectManager::Add(string key, UINT poolCount, wstring textureFile, Vector2 maxFrame, float speed, bool isAdditive)
{
    if (totalEffect.count(key) > 0)
        return;

    Effects effects(poolCount);

    for (Effect *& effect : effects)
    {
        effect = new Effect(textureFile, maxFrame, speed, isAdditive);
    }

    totalEffect[key] = effects;
}

void EffectManager::Play(string key, Vector2 pos)
{
    if (totalEffect.count(key) == 0)
        return;

    for (Effect * effect : totalEffect[key])
    {
        if (!effect->Active())
        {
            effect->Play(pos);
            return;
        }
    }
}
