#pragma once

class Object : public Transform
{
public:
	Object(string key);
	virtual ~Object();

	void Update();
	void Render();

	void Animation();

	void SetAction(Action* action);

	void UpdateTransform();
	bool& AnimPlay() { return isAnimPlay; }
	float& AnimTime() { return animTime; }

	ObjectSample::InstanceData& GetInstanceData();

	void SetCollider(Vector2 size)
	{
		collider = new RectCollider(size);
		collider->SetParent(this);
		collider->UpdateWorld();
	}

	virtual void SetActive(bool isActive) 
	{
		this->isActive = isActive;
		if (!isActive)
			Scale() = { 0,0 };
		else
			Scale() = { 2,2 };

		UpdateWorld();
	}
	Action*& GetAction() { return action; }

	Collider* GetCollider() { return collider; }

	string tag = "";
	string effect = "";
	string isMelt = "MELT";
private:
	ObjectSample::InstanceData instanceData;
	Collider* collider = nullptr;
	float animTime = 0.0f;
	bool isAnimPlay = true;
	Action* action = nullptr;
};