#pragma once

class Move : public Action
{
private:
	const float MOVE_POWER = 48;
public:
	Move(Transform* target, Vector2* curFrame = nullptr);
	~Move();


	virtual void Update() override;

	void MoveTarget();
	void Animaion();
private:
	Transform* target;
	Vector2* curFrame;
	Vector2 endPos = {0,0};

	bool isMove = false;
};