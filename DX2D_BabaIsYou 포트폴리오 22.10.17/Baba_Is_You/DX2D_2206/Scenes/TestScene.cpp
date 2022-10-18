#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	quad = new Quad(L"Textures/Object/Image/GRASS_ALL.png");
	quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
	quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

	Transform transform;
	transform.Position() = { CENTER_X,CENTER_Y };
	transform.Scale() *= 2;
	transform.Rotation().z = 0;

	transform.UpdateWorld();

	instanceData.curFrame = Vector2(1, 1);
	instanceData.maxFrame = Vector2(16, 3);

	instanceData.transform = XMMatrixTranspose(transform.GetWorld());



	instanceBuffer = new VertexBuffer(&instanceData, sizeof(InstanceData), 1);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
}

void TestScene::Render()
{
	instanceBuffer->Set(1);

	quad->SetRender();

	DC->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void TestScene::PostRender()
{
}
