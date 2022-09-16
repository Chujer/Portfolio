#pragma once
#include "Character.h"
#include "Game/Effect.h"
#include "Game/Bullet.h"

// 애니메이션 전환 구현해야함 2022.05.06

class Mob_Potato : public Character
{
public:
	Mob_Potato(Vector3 position, Vector3 size, HitBox* target, bool Active);
	~Mob_Potato();
	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;
	virtual bool GetActive() override;
	virtual void SetActive(bool active) override;

	void Hit(int damage) { HP = HP - damage; }
	bool GetIsDeath() { return isDeath; }
	HitBox* GetHitBox() { return hitbox; }
	void SetHp() { HP = HP - 101; printf("%d", HP); }
	void loopAnimation(int count, wstring name);
	bool GetNextMob() { return goNextMob; }

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
	void AABB(Character* other);
	AnimationRect* GetAnimRect() { return animRect; }


	bool OBB();

private:
	class HitBox* target = nullptr;
	class HitBox* hitbox = nullptr;
	class Effect* ground = nullptr;
	class Effect* ground2 = nullptr;
	class Bullet* bullet[4];
	vector<AnimationClip*> clips;

	int bulletIndex = 0;
	int point = 0;

	int loopCount = -1;
	bool loopEnd = false;

	float attackSpeed = 22.0f;

	bool goNextMob = false;

	int HP = 400;
	int state;
	bool active = false;
	bool isDeath = false;
};

