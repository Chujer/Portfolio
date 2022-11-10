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

	//virtual void Render() override;

private:
	void SetStop();
	void SetPushObject(Vector2 nextPos);
	void SetFinishMove();
	void ParticlePlay(Vector2 pos);
	void GetColor();
private:
	Transform* target;
	Vector2* curFrame;
	Vector2 nextPos = {0,0};
	Vector2 endPos = {0,0};

	vector<Transform*> pushTargets;

	bool isMove = false;
	Float4 Color;
};