#include "Framework.h"

Object::Object(string key)
{
	tag = key;
	instanceData = ObjectSample::Get()->GetInstanceData(key);
	Position() = { CENTER_X,CENTER_Y };
	Rotation().z =0;
	Scale() = { 2.0f,2.0f };
	UpdateTransform();
}

Object::~Object()
{
	delete collider;
}

void Object::Update()
{
	if (!isActive)
		return;

	if (action != nullptr)
		action->Update();

	if (isAnimPlay)
		Animation();
	else
		instanceData.curFrame.y = 0;
	UpdateWorld();
	if (collider != nullptr)
	{
		collider->UpdateWorld();
	}
}

void Object::Render()
{
	if (!isActive)
		return;

	if (collider != nullptr)
	{
		collider->Render();
	}
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

void Object::SetAction(Action* action)
{
	if (this->action != nullptr)
		delete this->action;

	this->action = action;
}

void Object::UpdateTransform()
{
	UpdateWorld();
	instanceData.transform = XMMatrixTranspose(GetWorld());
}

ObjectSample::InstanceData& Object::GetInstanceData()
{
	return instanceData;
}
