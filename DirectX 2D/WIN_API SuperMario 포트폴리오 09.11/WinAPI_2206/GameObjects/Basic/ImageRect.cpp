#include "Framework.h"

ImageRect::ImageRect()
{
    camRect = new Rect();
}

ImageRect::ImageRect(Texture * texture)
    : texture(texture)
{
    size = texture->GetSize();
    camRect = new Rect(pos, size);
}

ImageRect::~ImageRect()
{
    delete camRect;
}

void ImageRect::Render(HDC hdc, POINT curFrame)
{
    if (!isActive) return;

    texture->Render(hdc, this, curFrame);
}

void ImageRect::Render(HDC hdc, int alpha, POINT curFrame)
{
    if (!isActive) return;

    texture->Render(hdc, this, alpha, curFrame);
}

void ImageRect::CamRender(HDC hdc, POINT curFrame)
{
    if (!isActive) return;

    camRect->Pos() = pos - Camera::Get()->GetPos();
    texture->Render(hdc, camRect, curFrame);
}

void ImageRect::Update()
{
    if (firstCamPos != Camera::Get()->GetPos())
    {
        pos += firstCamPos - Camera::Get()->GetPos();
        firstCamPos = Camera::Get()->GetPos();
    }

}

void ImageRect::SetTexture(Texture * texture)
{
    this->texture = texture;
    size = texture->GetSize();
    camRect->Size() = size;
}