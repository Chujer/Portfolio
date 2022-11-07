#pragma once

class Action
{
public:
	Action();
	~Action();

	virtual void Update() {};
	virtual void Render();

protected:
	vector<Particle*> particles;
};