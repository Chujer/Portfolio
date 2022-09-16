#include "Framework.h"
#include "Text.h"

Text::Text(Vector3 position, Vector3 size, float rotation, wstring path)
	:position(position), size(size), rotation(rotation)
{
	
	//vertices
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = Vector2(0, 0);
	}

	//vertexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices);
	}

	//indexBuffer
	{
		indices = { 0,1,2,0,3,1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	//vertexshader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	//pixelshader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}


	//inputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}

	wb = new WorldBuffer();

	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFile
		(
			DEVICE,
			path.c_str(),
			nullptr,
			nullptr,
			&srv,
			nullptr
		);
		CHECK(hr);
	}
}

Text::Text(Vector3 position, Vector3 size, float rotation)
	:position(position), size(size), rotation(rotation)
{
	//vertices
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = Vector3(0.0f, 0.0f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		vertices[1].position = Vector3(1.0f, 1.0f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		vertices[2].position = Vector3(1.0f, 0.0f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		vertices[3].position = Vector3(0.0f, 1.0f, 0.0f);
		vertices[3].uv = Vector2(0, 0);

		/*vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = Vector2(0, 0);*/
	}

	//vertexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	//indexBuffer
	{
		indices = { 0, 1, 2, 0, 3, 1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	//vertexshader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	//pixelshader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	//inputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}


	wb = new WorldBuffer();
}

Text::Text(Vector3 position, Vector3 size, bool changePoint, float rotation)
	:position(position), size(size), rotation(rotation)
{
	//vertices
	{
		vertices.assign(4, VertexTexture());

		vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[0].uv = Vector2(0, 1);

		vertices[1].position = Vector3(0.5f, 0.5f, 0.0f);
		vertices[1].uv = Vector2(1, 0);

		vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
		vertices[2].uv = Vector2(1, 1);

		vertices[3].position = Vector3(-0.5f, 0.5f, 0.0f);
		vertices[3].uv = Vector2(0, 0);
	}

	//vertexBuffer
	{
		vb = new VertexBuffer();
		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	//indexBuffer
	{
		indices = { 0, 1, 2, 0, 3, 1 };

		ib = new IndexBuffer();
		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
	}

	//vertexshader
	{
		vs = new VertexShader();
		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
	}

	//pixelshader
	{
		ps = new PixelShader();
		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
	}

	//inputLayout
	{
		il = new InputLayout();
		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
	}


	wb = new WorldBuffer();
}

Text::~Text()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(ib);
	SAFE_DELETE(il);
	SAFE_DELETE(wb);
	SAFE_DELETE(ps);
	SAFE_DELETE(vs);
	SAFE_RELEASE(srv);
}

void Text::SetShader(wstring shaderPath)
{
	vs->Clear();
	ps->Clear();

	vs->Create(shaderPath, "VS");
	ps->Create(shaderPath, "PS");
}

void Text::Update()
{
	UpdateWorld();
	Move();
}

void Text::UpdateWorld()
{
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	world = S * R * T;
	wb->SetWorld(world);


}

void Text::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();
	wb->SetVSBuffer(0);
	if(srv != nullptr)
		DC->PSSetShaderResources(0, 1, &srv);

	DC->DrawIndexed(ib->GetCount(), 0, 0);
}

void Text::Move()
{
	/*if (Keyboard::Get()->Down('W'))
		position.y += 100 * Time::Delta();
	else if (Keyboard::Get()->Down('S'))
		position.y -= 100 * Time::Delta();

	if (Keyboard::Get()->Down('D'))
		position.y += 100 * Time::Delta();
	else if (Keyboard::Get()->Down('A'))
		position.y += 100 * Time::Delta();*/
}

void Text::GUI()
{

}

string Text::MakeLabel(string preFix)
{
	return string();
}

void Text::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void Text::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}
