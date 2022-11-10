#pragma once

#include <Utilities/Animator.h>
#include "Game/Bullet.h"
#include "Game/HitBox.h"
#include "Game/Mob_Potato.h"
#include "Game/Mob_onion.h"
#include "Game/Mob_carrot.h"

class BulletPosition
{
public:
	BulletPosition();

	Vector3 GetShootPosition(Vector3 position, string Xname, string Yname)
	{
		return Vector3(position.x + positionData.find(Xname)->second, position.y + positionData.find(Yname)->second, 0);
	}

private:
	unordered_map<string, float> positionData;
};

class Control
{
public:
	Control(Animator* animator, Vector3* position);
	void SetMob_Potato(Mob_Potato* m) { potato = m; }
	void SetMob_Onion(Mob_Onion* m) { onion = m; }
	void SetMob_Carrot(Mob_Carrot* m) { carrot = m; }
	~Control();

	void Update();

	void Right(DWORD key, float speed,HitBox* hitbox);
	void Left(DWORD key, float speed, HitBox* hitbox);
	void Aimming(DWORD key);
	void Up(DWORD key);
	void Down(DWORD key);
	void Jump(DWORD key, float speed, HitBox* hitbox);
	void Dash(DWORD key, float pos, HitBox* hitbox);
	void Death();
	void PlayerPositionYLock(HitBox *hitbox);
	void ChangeEffectPosition();


	bool GetPush_Left() { return is_PushLeft; }
	bool GetPush_Right() { return is_PushRight; }
	bool GetDash() { return is_Dash; }
	bool GetFacingLeft() { return is_FacingLeft; }


	void ChangeAnimation();
	void Attack(DWORD key);

	void Skiil(DWORD key, DWORD key2);

	void OBB();

private:
	Effect* shootEffect = nullptr;
	Bullet* bullet[30];
	Animator* animator = nullptr;
	Vector3* position = nullptr;
	BulletPosition* bulletPosition = nullptr;

	float shootSpeed = 0;
	bool shootEffectOn = false;
	bool shootEffectActive = false;
	bool is_FacingLeft = false;
	bool is_Duck = false;

	bool is_PushRight = false;
	bool is_PushLeft = false;
	bool is_PushUp = false;
	bool is_PushDown = false;
	bool is_JumpPush = false;		

	bool is_Move = false;
	bool is_DashOn = false;
	bool is_Dash = false;

	bool is_Jump = false;

	bool is_Aiming = false;
	bool is_Attack = false;

	bool is_Dath = false;
	float dashTime = 0.3f;
	float dashDeltTime = 0.0f;

	float LockPlayerPositionY = 60.0f;
	float LockHitboxPositionY = 110.0f;

	float deltaTime = 0.0f;
	float keyDown = 0.0f;
	float jumpPower = 1.0f;

	float jumpTime = 0.7f;
	float shallowJumpTime = 0.5f;		//기존 점프타임0.6 얕은점프0.4
	float jumpStopTime = jumpTime / 13;
	float shallowJumpStopTime = shallowJumpTime / 13;

	class Mob_Potato* potato = nullptr;
	class Mob_Onion* onion = nullptr;
	class Mob_Carrot* carrot = nullptr;
	
	float animWaitTime = 1.0f;

	float shootingTime = 0.0f;
	float shootWaitTime = 0.15f;

	int attack = 0;
};