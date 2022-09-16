#include "Framework.h"

Effect::Effect(Texture * texture, float frameUpdateTime, bool isLoop)
    : ImageRect(texture)
{
    isActive = false;

    animation = new Animation(texture->GetFrame(), frameUpdateTime);
    animation->SetDefault(isLoop);
    animation->SetEndEvent(bind(&Effect::Stop, this));    
}

Effect::~Effect()
{
    delete animation;
}

void Effect::Update()
{
    if (!isActive) return;

    animation->Update();
}

void Effect::Render(HDC hdc)
{
    ImageRect::Render(hdc, animation->GetFrame());
}

void Effect::Play(Vector2 pos)
{
    isActive = true;

    this->pos = pos;
    animation->Play();
}

void Effect::Stop()
{
    isActive = false;
}
