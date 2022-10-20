#include "Framework.h"
#include "BabaScene.h"

BabaScene::BabaScene()
{
	object = new Object("GRASS_16");
	object2 = new Object("GRASS_16");
	object->Position() = {200, CENTER_Y};
	object->UpdateTransform();
	
	instanceQuads["GRASS_16"] = new InstanceQuad("GRASS_16");
	instanceQuads["GRASS_16"]->AddPushDatas(object);
	instanceQuads["GRASS_16"]->AddPushDatas(object2);
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
	object->Position() += 100*DELTA;
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
