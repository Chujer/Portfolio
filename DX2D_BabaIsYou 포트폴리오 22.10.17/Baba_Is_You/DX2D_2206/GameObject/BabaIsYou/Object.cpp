#include "Framework.h"

Object::Object(string key)
{
	instanceData = ObjectSample::Get()->GetInstanceData(key);
	Position() = { CENTER_X,CENTER_Y };
	Rotation().z =0;
	Scale() = { 2.0f,2.0f };
	UpdateTransform();
}

Object::~Object()
{
}

void Object::Update()
{
	Animation();
	//UpdateWorld();
	//instanceData.transform = XMMatrixTranspose(GetWorld());
}

void Object::Render()
{
}


void Object::Animation()
{
	if (!isAnimPlay)
		return;
	animTime += DELTA;
	if (animTime > 0.2f)
	{
		instanceData.curFrame.y++;
		if (instanceData.curFrame.y == instanceData.maxFrame.y)
		{
			instanceData.curFrame.y = 0;
		}
		animTime = 0;
	}
}

void Object::UpdateTransform()
{
	UpdateWorld();
	instanceData.transform = XMMatrixTranspose(GetWorld());
}

ObjectSample::InstanceData Object::GetInstanceData()
{
	return instanceData;
}
