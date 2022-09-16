#include "Framework.h"

bool Texture::isDebugMode = false;

Texture::Texture(wstring imageFile, int widthSize, int heightSize, COLORREF transColor)
    : transColor(transColor)
{
    CreateBitmap(imageFile, widthSize, heightSize);
    
    imageFrame = { 1, 1 };
    cutSize = imageSize;
}

Texture::Texture(wstring imageFile, int widthSize, int heightSize, int widthFrame, int heightFrame, COLORREF transColor)
    : transColor(transColor)
{
    CreateBitmap(imageFile, widthSize, heightSize);

    imageFrame = { widthFrame, heightFrame };
    cutSize = { widthSize / widthFrame, heightSize / heightFrame };
}

Texture::~Texture()
{
    DeleteDC(memDC);
    DeleteObject(hbitmap);
}

void Texture::Render(HDC hdc, Rect * rect, POINT curFrame)
{
    if (isDebugMode)
        rect->LineRender(hdc);

    GdiTransparentBlt(
        hdc,
        (int)(rect->Left()), (int)(rect->Top()),
        (int)(rect->Size().x), (int)(rect->Size().y),
        memDC,
        cutSize.x * curFrame.x, cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        transColor
    );
}

void Texture::Render(HDC hdc, Rect * rect, float rate)
{
    if (isDebugMode)
        rect->LineRender(hdc);

    GdiTransparentBlt(
        hdc,
        (int)(rect->Left()), (int)(rect->Top()),
        (int)(rect->Size().x * rate), (int)(rect->Size().y),
        memDC,
        0, 0,
        (int)(cutSize.x * rate), cutSize.y,
        transColor
    );
}

void Texture::Render(HDC hdc, Rect * rect, int alpha, POINT curFrame)
{
    //alpha : 0 ~ 255
    blendFunc.SourceConstantAlpha = alpha;

    BitBlt(
        alphaMemDC,
        0, 0, cutSize.x, cutSize.y,
        hdc,
        (int)(rect->Left()),
        (int)(rect->Top()),
        SRCCOPY
    );

    GdiTransparentBlt(
        alphaMemDC,
        0, 0, imageSize.x, imageSize.y,
        memDC,
        0, 0, imageSize.x, imageSize.y,
        transColor
    );

    GdiAlphaBlend(
        hdc,
        (int)(rect->Left()), (int)(rect->Top()),
        (int)(rect->Size().x), (int)(rect->Size().y),
        alphaMemDC,
        cutSize.x * curFrame.x, cutSize.y * curFrame.y,
        cutSize.x, cutSize.y,
        blendFunc
    );
}

float Texture::GetPixelHeight(Vector2 pos)
{
    if (pos.y < 0.0f)
        pos.y = 0.0f;

    for (int i = (int)pos.y; i < imageSize.y; i++)
    {
        COLORREF color = GetPixel(memDC, (int)pos.x, i);

        if (color != transColor)
            return (float)i;
    }

    return (float)imageSize.y;
}

void Texture::CreateBitmap(wstring imageFile, int widthSize, int heightSize)
{
    HDC hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);
    alphaMemDC = CreateCompatibleDC(hdc);
    alphaBitmap = CreateCompatibleBitmap(hdc, widthSize, heightSize);
    ReleaseDC(hWnd, hdc);

    hbitmap = (HBITMAP)LoadImage(hInst, imageFile.c_str(), IMAGE_BITMAP,
        widthSize, heightSize, LR_LOADFROMFILE);

    if (hbitmap == nullptr)
        MessageBox(hWnd, imageFile.c_str(), L"경로나 이름이 틀림", MB_OK);

    SelectObject(memDC, hbitmap);
    SelectObject(alphaMemDC, alphaBitmap);

    imageSize = { widthSize, heightSize };
}
