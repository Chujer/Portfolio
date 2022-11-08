#pragma once

class Win : public Action
{
public:
	Win(Transform* target);
	~Win();

	virtual void Update() override;


private:
	Transform* target;
	
	bool isClear = false;
	float time = 0.0f;
};