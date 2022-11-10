#pragma once

class Enemy : public ImageRect
{
protected:
	enum ActionType
	{
		IDLE, DEATH,
		TUTLE_L, TUTLE_R,
		HIDDENDEATH
	};

	const float GRAVITY = 980.0f;
	const float DEATH_DELAY_TIME = 0.5f;

public:
	Enemy();
	~Enemy();

	virtual void Update() {};
	void Render(HDC hdc);

	virtual void Move();

	virtual void SetAniamtion() {};
	virtual void CreateAnimation() {};
	void IsOnTheGround(Vector2 Ground);
	void SetAction(ActionType type);

	void HiddenDeathMove();
	void HiddenDeathJump();
	bool& HiddenDeath() { return hiddenDeath; }

	void SetPosition(Vector2 position);

	bool& IsDeath() { return isDeath; }

	void ReturnMoveX();

	void InCave(bool isCave = false) 
	{ 
		this->isCave = isCave; 
		CreateAnimation();
	}
	void SetEvent(function<void()> Event) { this->Event = Event; }

protected:
	float speed = 200.0f;
	map<ActionType, Animation*> animations;
	ActionType curType = IDLE;

	bool isDeath = false;
	bool hiddenDeath = false;
	float DeathTime;
	float gravity = 0;

	function<void()> Event = nullptr;
	bool isCave;
	bool justOne = true;

	float velocity;
};