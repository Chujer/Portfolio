#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	test = new Particle("Particle/WinParticle.fx");
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
	delete test;
}

void TestScene::Update()
{
	test->Update();

}

void TestScene::Render()
{
	if (KEY_DOWN(VK_SPACE))
		test->Play({CENTER_X,CENTER_Y});
	test->Render();
}

void TestScene::PostRender()
{
}
