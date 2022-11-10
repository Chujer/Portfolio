#pragma once

class ProgressBar : public Rect
{
public:
    ProgressBar(Texture * frontTexture, Texture * backTexture, float maxValue = 100.0f);
    ~ProgressBar();

    void Render(HDC hdc);

    void SetValue(float value) { curValue = value; }

    float GetValue() { return curValue; }
private:
    Texture * frontTexture;
    Texture * backTexture;

    float maxValue;
    float curValue;
};