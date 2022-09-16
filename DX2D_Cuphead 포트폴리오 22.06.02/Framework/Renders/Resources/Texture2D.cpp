#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	:filePath(filePath)
{
	Textures::Load(this);
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D * texture, vector<Color>* pixels)
{
	D3D11_TEXTURE2D_DESC srcDesc;
	texture->GetDesc(&srcDesc);

	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));

	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	destDesc.Width = srcDesc.Width;
	destDesc.Height = srcDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srcDesc.Format;
	destDesc.SampleDesc = srcDesc.SampleDesc;

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex);
	CHECK(hr);
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	UINT* colors = new UINT[destDesc.Width * destDesc.Height];

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResource);
	{
		memcpy(colors, subResource.pData, sizeof(UINT) * destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);

	int pixelNum = destDesc.Width * destDesc.Height;

	UINT* colors1 = new UINT[destDesc.Width * destDesc.Height];
	UINT* colors2 = new UINT[destDesc.Width * destDesc.Height];
	UINT* colors3 = new UINT[destDesc.Width * destDesc.Height];
	UINT* colors4 = new UINT[destDesc.Width * destDesc.Height];

	for (int i = 0; i < pixelNum; i++)
	{
		colors1[i] = (colors[i] & 0xFF000000);
		colors2[i] = (colors[i] & 0x00FF0000);
		colors3[i] = (colors[i] & 0x0000FF00);
		colors4[i] = (colors[i] & 0x000000FF);

		colors2[i] = colors[i] >> 16;
		colors4[i] = colors[i] << 16;

		colors[i] = colors1[i] | colors2[i] | colors3[i] | colors4[i];
	}
	
	pixels->assign(&colors[0], &colors[destDesc.Width * destDesc.Height - 1]);

	SAFE_DELETE_ARRAY(colors);
	SAFE_RELEASE(destTex);
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.srv);
}

void Textures::Load(Texture2D * texture)
{
	HRESULT hr;
	TexMetadata metaData;

	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	UINT width = metaData.width;
	UINT height = metaData.height;

	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.width = width;
	desc.height = height;

	TextureDesc exist;
	bool bExist = false;
	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			bExist = true;
			exist = temp;

			break;
		}
	}

	if (bExist == true)
	{
		texture->srv = exist.srv;
	}
	else
	{
		ScratchImage image;

		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else
		{
			hr = LoadFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
}
