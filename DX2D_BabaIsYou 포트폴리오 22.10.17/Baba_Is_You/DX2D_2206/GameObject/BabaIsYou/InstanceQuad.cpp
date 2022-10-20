#include "Framework.h"

InstanceQuad::InstanceQuad(string key)
{
	ObjectSample::InstanceData data = ObjectSample::Get()->GetInstanceData(key);
	quad = new Quad(data.path, { 0,0 }, { 1 / data.maxFrame.x,1 / data.maxFrame.y });
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");
}

InstanceQuad::~InstanceQuad()
{
	delete quad;
	delete instanceBuffer;
	for (Object* object : objectDatas)
		delete object;
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
	instanceDatas.push_back(instanceData);

	if (instanceDatas.size() == 1)
		CreateInstanceBuffer();
	else
		instanceBuffer->Update(instanceDatas.data(), instanceDatas.size());

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

	DC->DrawIndexedInstanced(6, instanceDatas.size(), 0, 0, 0);
	for (Object* object : objectDatas)
	{
		if (object->Active())
			object->Render();
	}
}

void InstanceQuad::CreateInstanceBuffer()
{
	instanceBuffer = new VertexBuffer(instanceDatas.data(), sizeof(InstanceData), DESC_SIZE);
}
