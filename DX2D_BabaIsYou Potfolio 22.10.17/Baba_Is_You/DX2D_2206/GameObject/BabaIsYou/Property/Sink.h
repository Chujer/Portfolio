#pragma once

class Sink : public Action
{
public:
	Sink(Transform* target);
	~Sink();

	virtual void Update();

private:
	Transform* target;
};