#include "Framework.h"

InstanceQuad::InstanceQuad(string key)
{
	ObjectSample::InstanceData data = ObjectSample::Get()->GetInstanceData(key);
	quad = new Quad(data.path, { 0,0 }, { 1 / data.maxFrame.x,1 / data.maxFrame.y });
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

	CreateInstanceBuffer();
}

InstanceQuad::InstanceQuad(string key, int count)
{
	ObjectSample::InstanceData data = ObjectSample::Get()->GetInstanceData(key);
	quad = new Quad(data.path, { 0,0 }, { 1 / data.maxFrame.x,1 / data.maxFrame.y });
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

	CreateInstanceBuffer(count);
}

InstanceQuad::~InstanceQuad()
{
	delete quad;
	delete instanceBuffer;
	//for (Object* object : objectDatas)
	//	delete object;
}

void InstanceQuad::SetBufferSize(int count)
{
	delete instanceBuffer;
	instanceBuffer = new VertexBuffer(instanceDatas.data(), sizeof(InstanceData), count);
}

void InstanceQuad::AddPushDatas(Object* object)
{
	objectDatas.push_back(object);
	Vector2 size = Texture::Add(object->GetInstanceData().path)->GetSize();
	InstanceData instanceData;
	instanceData.curFrame = object->GetInstanceData().curFrame;
	instanceData.maxFrame = object->GetInstanceData().maxFrame;
	instanceData.transform = object->GetInstanceData().transform;
	object->SetCollider({size.x / object->GetInstanceData().maxFrame.x, size.y / object->GetInstanceData().maxFrame.y});
	instanceDatas[objectDatas.size() - 1] = instanceData;

	//instanceBuffer->Update(instanceDatas.data(), instanceDatas.size());
}

void InstanceQuad::Update()
{
	for (int i = 0; i < objectDatas.size(); i++)
	{
		objectDatas[i]->Update();
		instanceDatas[i].curFrame = objectDatas[i]->GetInstanceData().curFrame;
		instanceDatas[i].maxFrame = objectDatas[i]->GetInstanceData().maxFrame;
		instanceDatas[i].transform = XMMatrixTranspose(objectDatas[i]->GetWorld());
		
		instanceBuffer->Update(instanceDatas.data(), instanceDatas.size());
	}
	
}

void InstanceQuad::Render()
{
	instanceBuffer->Set(1);

	quad->SetRender();
	
	DC->DrawIndexedInstanced(6, objectDatas.size(), 0, 0, 0);

}

void InstanceQuad::ParticleRender()
{
	for (Object* object : objectDatas)
	{
		//if (object->Active())
		object->Render();
	}
}

void InstanceQuad::DeleteObject(Object* object)		//인스턴스 데이터의 오브젝트를 제거할때 사용
{
	delete* find(objectDatas.begin(), objectDatas.end(), object);
	objectDatas.erase(find(objectDatas.begin(), objectDatas.end(), object));
}

void InstanceQuad::CreateInstanceBuffer()
{
	instanceDatas.resize(DESC_SIZE);
	instanceBuffer = new VertexBuffer(instanceDatas.data(), sizeof(InstanceData), DESC_SIZE);
}

void InstanceQuad::CreateInstanceBuffer(UINT maxCount)
{
	instanceDatas.resize(maxCount);
	instanceBuffer = new VertexBuffer(instanceDatas.data(), sizeof(InstanceData), maxCount);
}
