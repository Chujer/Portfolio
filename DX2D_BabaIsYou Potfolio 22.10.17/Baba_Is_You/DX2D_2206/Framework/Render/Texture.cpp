#include "Framework.h"

unordered_map<wstring, Texture *> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView * srv, ScratchImage & image, wstring file)
    : srv(srv), image(move(image)), file(file)
{
}

Texture::~Texture()
{
    srv->Release();
}

Texture * Texture::Add(wstring file)
{
    if (textures.count(file) > 0)
        return textures[file];

    ScratchImage image;
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    ID3D11ShaderResourceView * srv;

    CreateShaderResourceView(DEVICE, image.GetImages(),
        image.GetImageCount(), image.GetMetadata(), &srv);

    Texture * texture = new Texture(srv, image, file);

    textures[file] = texture;

    return texture;
}

Texture * Texture::Add(wstring key, ID3D11ShaderResourceView * srv)
{
    if (textures.count(key) > 0)
        return textures[key];

    ScratchImage image;
    Texture * texture = new Texture(srv, image, key);

    textures[key] = texture;

    return texture;
}

void Texture::Delete()
{
    for (pair<wstring, Texture *> texture : textures)
        delete texture.second;
}

void Texture::PSSet(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, &srv);
}

Float4 Texture::GetCenterPixels()
{
    uint8_t* colors = image.GetPixels();
    UINT size = image.GetPixelsSize();

    float scale = 1.0f / 255.0f;

    vector<Float4> result(size / 4);

    for (UINT i = 0; i < result.size(); i++)
    {
        result[i].x = colors[i * 4 + 0] * scale;
        result[i].y = colors[i * 4 + 1] * scale;
        result[i].z = colors[i * 4 + 2] * scale;
        result[i].w = colors[i * 4 + 3] * scale;
        if (result[i].w != 0)
            return result[i];
    }

    return result[2000];
}