#pragma once

class Shell : public ImageRect
{
protected:
	enum ActionType
	{
		IDLE, RESURRECTION, HIDDENDEATH
	};

	const float GRAVITY = 980.0f;
	const float DEATH_DELAY_TIME = 0.5f;

	const float RESURRECTIONTIME = 3.0f;
	const float WAITTIME = 0.1f;

public:
	Shell(Tutle* tutle);
	~Shell();
	void Update();
	void Render(HDC hdc);

	void Move();

	void SetAniamtion();
	void CreateAnimation();
	void IsOnTheGround(Vector2 Ground);
	void SetAction(ActionType type);

	void SetHiddenDeath() { hiddenDeath = true; }
	bool GetHiddenDeath() { return hiddenDeath; }
	void HiddenDeathMove();
	void HiddenDeathJump();

	void SetPosition(Vector2 position);
	void SetDirection(Vector2 direction) { this->direction.x = direction.x; }

	void ReturnMoveX();

	void InCave(bool isCave = false)
	{
		this->isCave = isCave;
		CreateAnimation();
	}

	bool& Attack() { return isAttack; }
	bool& Ready() { return isReady; }

	void SetEvent(function<void()> Event) { this->Event = Event; }



private:
	bool isAttack = false;
	float thisTime = 0;
	float speed = 500.0f;
	map<ActionType, Animation*> animations;
	ActionType curType = IDLE;

	float gravity = 0;
	Vector2 direction = { 0,0 };
	function<void()> Event = nullptr;

	float swapTime = 0;

	Tutle* tutle;

	bool isReady = true;
	bool hiddenDeath = false;
	bool isCave;
	bool justOne = true;
	float velocity;
};