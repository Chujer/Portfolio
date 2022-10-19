#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	objectData = new Object("Flag");
	quad = new Quad(objectData->GetInstanceData().path, {0,0},
		{1 / objectData->GetInstanceData().maxFrame.x,1 / objectData->GetInstanceData().maxFrame.y});
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");


	InstanceData instanceData;
	instanceData.curFrame = objectData->GetInstanceData().curFrame;
	instanceData.maxFrame = objectData->GetInstanceData().maxFrame;
	instanceData.transform = objectData->GetInstanceData().transform;

	instanceBuffer = new VertexBuffer(&instanceData, sizeof(instanceData), 1);
	/*quad = new Quad(L"Textures/Object/Image/GRASS_ALL.png", {0,0}, {1 / 16.0f,1 / 3.0f});
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

	Transform transform;
	transform.Position() = { CENTER_X,CENTER_Y };
	transform.Scale() *= 2;
	transform.Rotation().z = 0;

	transform.UpdateWorld();

	instanceData.curFrame = Vector2(0, 0);
	instanceData.maxFrame = Vector2(16, 300);

	instanceData.transform = XMMatrixTranspose(transform.GetWorld());



	instanceBuffer = new VertexBuffer(&instanceData, sizeof(InstanceData), 1);*/
}

TestScene::~TestScene()
{
	delete objectData;
	delete quad;
}

void TestScene::Update()
{
	objectData->Update();
	instanceData.curFrame = objectData->GetInstanceData().curFrame;
	instanceData.maxFrame = objectData->GetInstanceData().maxFrame;
	instanceData.transform = XMMatrixTranspose(objectData->GetWorld());
	instanceBuffer->Update(&instanceData, 1);

	/*time += DELTA;

	if (time > 0.2f)
	{
		temp++;
		if (temp > 2)
			temp = 0;
		instanceData.curFrame = Vector2(0, temp);
		instanceBuffer = new VertexBuffer(&instanceData, sizeof(InstanceData), 1);
		time = 0;
	}*/
}

void TestScene::Render()
{
	instanceBuffer->Set(1);

	quad->SetRender();

	DC->DrawIndexedInstanced(6, 1, 0, 0, 0);
	/*instanceBuffer->Set(1);

	quad->SetRender();

	DC->DrawIndexedInstanced(6, 1, 0, 0, 0);
	*/
}

void TestScene::PostRender()
{
}
