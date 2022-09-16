#pragma once

class Texture
{
private:
    friend class TextureManager;

    Texture(wstring imageFile,
        int widthSize, int heightSize, COLORREF transColor = MAGENTA);
    Texture(wstring imageFile,
        int widthSize, int heightSize, int widthFrame, int heightFrame,
        COLORREF transColor = MAGENTA);
    ~Texture();

public:
    void Render(HDC hdc, class Rect * rect, POINT curFrame = { 0, 0 });
    void Render(HDC hdc, class Rect * rect, float rate);

    void Render(HDC hdc, class Rect * rect, int alpha, POINT curFrame = { 0, 0 });

    float GetPixelHeight(Vector2 pos);

    Vector2 GetSize() { return Vector2(cutSize); }
    POINT GetFrame() { return imageFrame; }
    HDC GetMemDC() { return memDC; }

    static void SwichDebug() { isDebugMode = !isDebugMode; }
private:
    void CreateBitmap(wstring imageFile, int widthSize, int heightSize);

private:
    HDC memDC;
    HDC alphaMemDC;
    HBITMAP hbitmap;
    HBITMAP alphaBitmap;

    COLORREF transColor;

    BLENDFUNCTION blendFunc;
    

protected:
    POINT imageSize;
    POINT imageFrame;
    POINT cutSize;

    static bool isDebugMode;
};