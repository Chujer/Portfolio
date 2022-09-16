#include "Framework.h"

ProgressBar::ProgressBar(Texture * frontTexture, Texture * backTexture, float maxValue)
    : frontTexture(frontTexture), backTexture(backTexture),
    maxValue(maxValue), curValue(maxValue)
{
    size = frontTexture->GetSize();
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Render(HDC hdc)
{
    backTexture->Render(hdc, this);
    frontTexture->Render(hdc, this, curValue / maxValue);
}
