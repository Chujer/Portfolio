#pragma once

class Object : public Transform
{
public:
	Object(string key);
	~Object();

	void Update();
	void Render();

	void Animation();

	void UpdateTransform();

	ObjectSample::InstanceData GetInstanceData();

private:
	ObjectSample::InstanceData instanceData;
	float animTime = 0.0f;
	bool isAnimPlay = true;
};