#pragma once

class Defeat : public Action
{
public:
	Defeat(Transform* target);
	~Defeat();

	virtual void Update() override;


private:
	Transform* target;
};