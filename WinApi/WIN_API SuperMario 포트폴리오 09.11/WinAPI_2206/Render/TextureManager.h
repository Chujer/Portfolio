#pragma once

class TextureManager : public Singleton<TextureManager>
{
public:
    TextureManager();
    ~TextureManager();

    Texture * Add(wstring imageFile,
        int widthSize, int heightSize, COLORREF transColor = MAGENTA);
    Texture * Add(wstring imageFile,
        int widthSize, int heightSize, int widthFrame, int heightFrame,
        COLORREF transColor = MAGENTA);

    Texture * Find(wstring imageFile);

private:
    unordered_map<wstring, Texture *> textures;
};