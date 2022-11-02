#pragma once

class Hot : public Action
{
public:
	Hot(Transform* target,string tag);
	~Hot();
	virtual void Update();

private:
	Transform* target;
	string tag;
};