#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox(RectEdge * edge)
{
}

BoundingBox::~BoundingBox()
{
	SAFE_RELEASE(blend[0]);
	SAFE_RELEASE(blend[1]);

	SAFE_DELETE(wb);
	SAFE_DELETE(cb);

	SAFE_DELETE(il);

	SAFE_DELETE(vs);
	SAFE_DELETE(ps);

	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void BoundingBox::Init()
{
	vertices.assign(4, VertexColor());

	vertices[0].position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].position = Vector3(0.0f, edge->LT.y - edge->RB.y, 0.0f);
	vertices[2].position = Vector3(edge->RB.x - edge->LT.x, 0.0f, 0.0f);
	vertices[3].position = Vector3(edge->RB.x - edge->LT.x, edge->LT.y - edge->RB.y, 0.0f);

	for (VertexColor& v : vertices)
		v.color = Color(1.0f, 0, 0, 1.0f);

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	indices.resize(8, UINT());
	indices = { 0,1,1,3,3,2,2,0 };

	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"CollisionShader.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"CollisionShader.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexColor::descs, VertexColor::count, vs->GetBlob());

	wb = new WorldBuffer();
	cb = new CollisionBuffer();

	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &blend[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &blend[1]);
	}
}

void BoundingBox::Update()
{
	D3DXMatrixTranslation(&world, edge->LT.x, edge->RB.y, 0.0f);
	wb->SetWorld(world);
}

void BoundingBox::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();

	wb->SetVSBuffer(0);
	cb->SetPSBuffer(0);

	DC->OMSetBlendState(blend[1], nullptr, 0xffffffff);
	DC->DrawIndexed(ib->GetCount(), 0, 0);
	DC->OMSetBlendState(blend[0], nullptr, 0xffffffff);
}

function<void()> BoundingBox::GetFuncPtr()
{
	return bind(&CollisionBuffer::SwitchRender, cb);
}

bool BoundingBox::AABB(BoundingBox * a, BoundingBox * b)
{
	if (a == nullptr || b == nullptr) return false;

	RectEdge aRect = *a->edge;
	RectEdge bRect = *b->edge;

	if (aRect.RB.x >= bRect.LT.x &&
		aRect.LT.x <= bRect.RB.x &&
		aRect.LT.y >= bRect.RB.y &&
		aRect.RB.y <= bRect.LT.y)
		return true;
	else
		return false;
}

bool BoundingBox::CheckOutSide()
{
	if (edge->LT.x <= 0
		|| edge->RB.x >= WinMaxWidth
		|| edge->LT.y <= 0
		|| edge->RB.y >= WinMaxHeight)
		return true;
	else
		return false;
}

OBB::OBB(TransformData * transform)
	:transform(transform)
{
}

OBB::~OBB()
{
}

void OBB::Calculation()
{
	RectEdge r = (*transform).edge;
	centerPos.x = (r.RB.x + r.LT.x) * 0.5f;
	centerPos.y = (r.RB.y + r.LT.y) * 0.5f;
	centerPos.z = 0.0f; //1

	Vector3 position = (*transform).position;
	centerW = (r.RB - position) * 0.5f;
	centerW.z = 0.0f;

	centerH = (r.LT - position) * 0.5f;
	centerH.z = 0.0f;
}

bool OBB::CheckIntersect(OBB * a, OBB * b)
{
	if (a->GetTransform()->edge.LT.x > 1 && b->GetTransform()->edge.LT.x)
	{
		TransformData* ta = a->transform;
		TransformData* tb = b->transform;

		Vector3 dist = b->centerPos - a->centerPos;
		//중심축 사이의 거리

		vector<Vector3> vecs;
		vecs.push_back(a->centerH);
		vecs.push_back(a->centerW);
		vecs.push_back(b->centerH);
		vecs.push_back(b->centerW);
		//위,아래 구하는 좌표

		vector<Vector3> separatedAxises;
		separatedAxises.push_back(Vector3(cosf(D3DXToRadian(ta->rotation)), sinf(D3DXToRadian(ta->rotation)), 0.0f));
		separatedAxises.push_back(Vector3(cosf(D3DXToRadian(ta->rotation + 90.0f)), sinf(D3DXToRadian(ta->rotation + 90.0f)), 0.0f));
		separatedAxises.push_back(Vector3(cosf(D3DXToRadian(tb->rotation)), sinf(D3DXToRadian(tb->rotation)), 0.0f));
		separatedAxises.push_back(Vector3(cosf(D3DXToRadian(tb->rotation + 90.0f)), sinf(D3DXToRadian(tb->rotation + 90.0f)), 0.0f));
		//

		float sum = 0.0f;

		for (int i = 0; i < separatedAxises.size(); i++)
		{
			sum = 0;
			for (int j = 0; j < vecs.size(); j++)
				sum += abs(D3DXVec3Dot(&separatedAxises[i], &vecs[j]));

			if (abs(D3DXVec3Dot(&dist, &separatedAxises[i])) > sum)
				return false;
		}

		return true;
	}
	else
		return false;
}
