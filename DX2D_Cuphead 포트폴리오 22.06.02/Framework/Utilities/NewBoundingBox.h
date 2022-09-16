#pragma once

struct RectEdge
{
	Vector3 LT;
	Vector3 RB;
};

struct TransformData
{
	RectEdge edge;
	Vector3 position;
	Vector3 size;
	float rotation;
};

class CollisionBuffer : public ShaderBuffer
{
public:
	CollisionBuffer() : ShaderBuffer(&data, sizeof(data))
	{
		data.isOn = 1;
	}

	void SwitchRender() { data.isOn = !data.isOn; }

	struct Data
	{
		int isOn;
		Vector3 dummy;
	};

private:
	Data data;
};

class BoundingBox
{
public:
	BoundingBox(RectEdge* edge);
	~BoundingBox();

	void Init();

	void Update();
	void Render();
	function<void()> GetFuncPtr();


	static bool AABB(BoundingBox* a, BoundingBox* b);
	bool CheckOutSide();

private:
	RectEdge* edge = nullptr;

	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	WorldBuffer* wb = nullptr;
	Matrix world;

	Vector3 position;
	Vector3 size;
	float rotation;

	CollisionBuffer* cb = nullptr;
	ID3D11BlendState* blend[2];
};

class OBB
{
public:
	OBB(TransformData* transform);
	~OBB();

	void Calculation();
	static bool CheckIntersect(OBB* a, OBB* b);

private:
	TransformData* transform;

	Vector3 centerW = Value::ZeroVec3;
	Vector3 centerH = Value::ZeroVec3;
	Vector3 centerPos = Value::ZeroVec3;
};