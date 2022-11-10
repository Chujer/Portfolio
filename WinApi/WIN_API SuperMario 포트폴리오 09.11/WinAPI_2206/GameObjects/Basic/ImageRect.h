#pragma once

class ImageRect : public Rect
{
public:
    ImageRect();
    ImageRect(Texture * texture);
    ~ImageRect();

    void Render(HDC hdc, POINT curFrame = { 0, 0 });
    void Render(HDC hdc, int alpha, POINT curFrame = { 0, 0 });
    void CamRender(HDC hdc, POINT curFrame = { 0, 0 });
    void Update();
    void SetTexture(Texture * texture);
    Texture * GetTexture() { return texture; }
protected:
    Texture * texture;
    Rect * camRect;
    Vector2 firstCamPos;
};