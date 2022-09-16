#pragma once

class Effect : public ImageRect
{
public:
    Effect(Texture * texture, float frameUpdateTime = 0.1f, bool isLoop = false);
    ~Effect();

    void Update();
    void Render(HDC hdc);

    void Play(Vector2 pos);
    void Stop();

private:
    Animation * animation;
};