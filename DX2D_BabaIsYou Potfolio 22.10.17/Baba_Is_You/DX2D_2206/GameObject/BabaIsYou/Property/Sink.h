#pragma once

class Sink : public Action
{
public:
	Sink(Transform* target, string tag);
	~Sink();

	virtual void Update() override;
	virtual void Render() override;

private:
	Transform* target;
	string tag;
};