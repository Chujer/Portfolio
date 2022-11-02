#pragma once

class Sink : public Action
{
public:
	Sink(Transform* target, string tag);
	~Sink();

	virtual void Update();

private:
	Transform* target;
	string tag;
};