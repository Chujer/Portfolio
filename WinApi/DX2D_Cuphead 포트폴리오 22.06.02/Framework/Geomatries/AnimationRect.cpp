#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	:Text(position, size, 0.0f)
{
	SetShader(ShaderPath + L"Animation.hlsl");

	{
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CraeteSampler(&desc, &point[0]);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CraeteSampler(&desc, &point[1]);
	}

	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}

	edge = new RectEdge();
	box = new BoundingBox(edge);
	obb = new OBB(&transform);
}

AnimationRect::AnimationRect(Vector3 position, Vector3 size, bool changePoint)
	:Text(position, size, changePoint ,0.0f)
{
	SetShader(ShaderPath + L"Animation.hlsl");
	this->changePoint = changePoint;
	{
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CraeteSampler(&desc, &point[0]);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CraeteSampler(&desc, &point[1]);
	}

	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}

	edge = new RectEdge();
	box = new BoundingBox(edge);
	obb = new OBB(&transform);
}

AnimationRect::~AnimationRect()
{
}

void AnimationRect::Update()
{
	__super::Update();

	D3DXVec3TransformCoord(&edge->LT, &vertices[3].position, &world);
	D3DXVec3TransformCoord(&edge->RB, &vertices[2].position, &world);
	//D3DXMatrixTranslation(&world, edge->LT.x, edge->RB.y, 0.0f);


	MapVertexBuffer();
	{
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;
	}
	UnmapVertexBuffer();

	
	if(changePoint==true)
		transform.edge = *edge;
	else
		transform.edge = *edge;
	transform.position = position;
	transform.size = size;
	transform.rotation = rotation;
	obb->Calculation();

}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFFF);
	__super::Render();
	DC->PSSetSamplers(0, 1, &point[0]);
	DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFFF);
}

void AnimationRect::Move()
{

}
