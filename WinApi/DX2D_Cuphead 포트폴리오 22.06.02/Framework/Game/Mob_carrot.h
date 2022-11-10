#pragma once
#include "Character.h"
class Mob_Carrot: public Character
{
public:
	Mob_Carrot(Vector3 position, Vector3 size, HitBox* target, bool Active);
	~Mob_Carrot();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;
	virtual bool GetActive() override;
	virtual void SetActive(bool active) override;

	void SetHp() { HP = HP - 101; }
	int getHp() { return HP; }
	
	Bullet* GetMissile(int index) { return missile[index]; }
	bool GetIsDeath() { return isDeath; }
	HitBox* GetHitBox() { return hitbox; }

	AnimationRect* GetAnimRect() { return animRect; }

	void loopAnimation(int count, wstring name); 
	bool GetLoopEnd()
	{
		if (loopEnd == true)
		{
			loopCount = -1;
			loopEnd = false;
			return true;
		}
		else
			return false;
	}
	bool OBB();
	void Hit(int damage) { HP = HP - damage; }

private:
	class HitBox* hitbox = nullptr;
	class HitBox* target = nullptr;
	class Effect* beamEffect = nullptr;
	class Bullet* missile[5];
	class Bullet* beam[4];
	class Effect* ground = nullptr;

	vector<AnimationClip*> clips;

	int loopCount = -1;
	bool loopEnd = false;
	int state;
	int missileIndex = 0;
	int beamIndex = 0;
	int DeathAniCount = 0;

	int HP = 400;

	Vector3 targetPosition;

	float missileDelayTime = 2.0f;
	float missileTime = 0;

	bool onBeamTime = false;
	bool beamOn = false;

	float beamTime = 0;
	float beamDelayTime = 0.2f;
	
	float attack2Time = 0;
	float attack2CountinuingTime = 8.0f;

	int effectLoop = 0;

	float beamShootTime = 0;
	float beamShootDelayTime = 4.5f;


	int loopAniCount_Missile = 3;

	int point = 0;
	bool isDeath = false;
	bool isActive = false;
};

