#pragma once

class Action
{
public:
	Action();
	~Action();

	virtual void Update() {};
	void Render();

protected:
	vector<Particle*> particles;
};