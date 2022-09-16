#pragma once
#include "Geomatries/AnimationRect.h"
#include "Game/Character.h"
#include "Game/HitBox.h"
#include "Game/Effect.h"
class Bullet
{
public:
	Bullet(Vector3 position, Vector3 size, float speed, wstring path, float rotation = 0);
	~Bullet();
	void SetActive(bool active);
	

	void SetPlayerBullet(wstring path);
	void SetPlayerBulletInfo(Vector3 position, float rotation, wstring path);
	void SetPotatoBullet(wstring path);
	void SetPotatoBulletPosition();
	void SetOnionBullet(wstring path);
	void SetOnionBulletPosition(bool isLeft);
	void SetCarrotBullet(wstring path);
	void SetCarrotBulletPosition();
	void SetOnionBulletPosition();
	

	void SetTarget(HitBox* target)
	{
		this->target = target;
	}
	void SetTargetPosition(Vector3 position)
	{
		targetPosition = position;
		lockOn = true;
	}
	void SetBulletDath(bool dath) { this->dath = dath; }
	void SetHitBullet(int damage) { hp = hp - damage; }

	bool GetActive() { return active; }
	AnimationRect* GetAnimRect() { return tex; }
	int GetDamage() { return damage; }
	bool GetBulletDath() { return dath; }
	Effect* GetDathAni() { return bulletDeathAni; }
	HitBox* GetHitBox() { return hitbox; }
	
	void Update();

	void PlayerBulletUpdate();
	void PotatoBulletUpdate();
	void OnionBulletUpdate();
	void CarrotBulletUpdate();
	void CarrotBeamUpdate();

	void UpdateData();

	//bool AABB(BoundingBox* other) { return tex->GetBox()->AABB(other); }



private:
	AnimationRect* tex = nullptr;
	HitBox* hitbox = nullptr;
	Effect* bulletDeathAni = nullptr;
	class ShadedBuffer* sb = nullptr;

	int hp = 12;
	float dathTime = 0.0f;
	bool dath = false;
	int damage;
	int mode;
	float speed;
	bool isParry=false;
	bool active = false;
	float base = 0;
	float turnRotation = 0;
	float height = 0;
	bool lockOn = true;


	Vector3 targetPosition;
	/*
	float returnPosition = 0.0f;
	float returnPositionDelay = 0.3f;*/

	Vector3 nMovePoint;
	Vector3 respawn;
	Vector3 hitBoxRespawn;
	Vector3 hitBoxSize;
	Vector3 randPosition;
	wstring animname;
	HitBox* target;
	AnimationClip* clip;
	vector<AnimationClip*> clips;
	Animator* animator = nullptr;
};

