#pragma once

class Text
{
public:
	Text(Vector3 position, Vector3 size, float rotation, wstring path);
	Text(Vector3 position, Vector3 size, float rotation = 0.0f);
	Text(Vector3 position, Vector3 size, bool ChangePoint, float rotation = 0.0f);
	virtual ~Text();

	void SetSRV(ID3D11ShaderResourceView* srv) { this->srv = srv; }
	void SetShader(wstring shaderPath);
	
	void Update();
	void UpdateWorld();
	void Render();

	void SetPosition(Vector3 position) { this->position = position;}
	void SetSize(Vector3 size) { this->size = size; }
	void SetRotation(float rotation) { this->rotation = rotation; }


	//void SetChangePoint() { changePoint = true; }

	Vector3 GetPosition() { return position; }
	Vector3 GetSize() { return size; }
	float GetRotation() { return rotation; }

	virtual void Move();

	void GUI();

	string MakeLabel(string preFix);

	void MapVertexBuffer();
	void UnmapVertexBuffer();

protected:
	vector<VertexTexture> vertices;
	vector<uint> indices;

	D3D11_MAPPED_SUBRESOURCE subResource;

	VertexBuffer* vb = nullptr;
	IndexBuffer* ib = nullptr;
	InputLayout* il = nullptr;

	WorldBuffer* wb = nullptr;

	PixelShader* ps = nullptr;
	VertexShader* vs = nullptr;

	Vector3 position;
	Vector3 size;
	float rotation;

	bool changePoint = false;

	Matrix world;
	Matrix S, R, T;

	ID3D11ShaderResourceView* srv = nullptr;


};