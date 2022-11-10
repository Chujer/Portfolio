#pragma once

class Action
{
public:
	Action();
	virtual ~Action();

	virtual void Update() {};
	virtual void Render();

protected:
	vector<Particle*> particles;
};