#include "Framework.h"

InstanceQuad::InstanceQuad(ObjectSample::InstanceData data)
{
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

	InstanceData instanceData;
	instanceData.curFrame = object->GetInstanceData().curFrame;
	instanceData.maxFrame = object->GetInstanceData().maxFrame;
	instanceData.transform = object->GetInstanceData().transform;
	instanceDatas.push_back(instanceData);

	if (instanceDatas.size() == 1)
		CreateInstanceBuffer();
	else
		instanceBuffer->Update(instanceDatas.data(), instanceDatas.size());
		//CreateInstanceBuffer();

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
}

void InstanceQuad::CreateInstanceBuffer()
{
	instanceBuffer = new VertexBuffer(instanceDatas.data(), sizeof(InstanceData), instanceDatas.size());
}
