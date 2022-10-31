#pragma once

class Hot : public Action
{
public:
	Hot(Transform* target);
	~Hot();
	virtual void Update();

private:
	Transform* target;
};