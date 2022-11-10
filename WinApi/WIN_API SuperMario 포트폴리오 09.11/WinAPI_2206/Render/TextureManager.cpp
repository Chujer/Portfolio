#include "Framework.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
    for (pair<wstring, Texture *> texture : textures)
        delete texture.second;

    textures.clear();
}

Texture * TextureManager::Add(wstring imageFile, int widthSize, int heightSize, COLORREF transColor)
{
    Texture * texture = Find(imageFile);

    if (texture != nullptr)
        return texture;

    texture = new Texture(imageFile, widthSize, heightSize, transColor);
    textures[imageFile] = texture;

    return texture;
}

Texture * TextureManager::Add(wstring imageFile, int widthSize, int heightSize, int widthFrame, int heightFrame, COLORREF transColor)
{
    Texture * texture = Find(imageFile);

    if (texture != nullptr)
        return texture;

    texture = new Texture(imageFile, widthSize, heightSize,
        widthFrame, heightFrame, transColor);
    textures[imageFile] = texture;

    return texture;
}

Texture * TextureManager::Find(wstring imageFile)
{
    if (textures.count(imageFile) > 0)
        return textures[imageFile];

    return nullptr;
}
