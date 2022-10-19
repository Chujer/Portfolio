#include "Framework.h"
#include "BabaScene.h"

BabaScene::BabaScene()
{
	object = new Object("Flag");
	object2 = new Object("Flag");
	object->Position() = {200, CENTER_Y};
	object->UpdateTransform();
	
	instanceQuads["Flag"] = new InstanceQuad(ObjectSample::Get()->GetInstanceData("Flag"));
	instanceQuads["Flag"]->AddPushDatas(object);
	instanceQuads["Flag"]->AddPushDatas(object2);
}

BabaScene::~BabaScene()
{
	for (pair<string, InstanceQuad*> instanceQuad : instanceQuads)
	{
		delete instanceQuad.second;
	}
}

void BabaScene::Update()
{
	for (pair<string, InstanceQuad*> instanceQuad : instanceQuads)
	{
		instanceQuad.second->Update();
	}
}

void BabaScene::Render()
{
	for (pair<string, InstanceQuad*> instanceQuad : instanceQuads)
		instanceQuad.second->Render();
}

void BabaScene::PostRender()
{
}
