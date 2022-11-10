#pragma once

class Hot : public Action
{
private:
	const float PARTICLE_DELAY = 1.0f;
public:
	Hot(Transform* target,string tag);
	~Hot();
	virtual void Update() override;

private:
	Transform* target;
	string tag;
	float time = 0.0f;

	int randNum = 0;
};