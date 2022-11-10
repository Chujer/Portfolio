#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player(Vector3 position, Vector3 size);
	~Player();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Move() override;
	virtual bool GetActive() override;
	virtual void SetActive(bool active) override;
	void SetMob_Potato(Mob_Potato* m) { control->SetMob_Potato(m); }
	void SetMob_Onion(Mob_Onion* m) { control->SetMob_Onion(m); }
	void SetMob_Carrot(Mob_Carrot* m) { control->SetMob_Carrot(m); }
	
	void SetHit() 
	{ 
		hit = true;
		HP = HP- 1;
	}

	int GetHP() {
		return HP;
	}
	AnimationRect* GetAnimRect() { return animRect; }
	HitBox* GetHitBox() { return hitbox; }
	bool GetHit() { return hit; }

	void PlayerBulletOBB();
private:
	class HitBox* hitbox = nullptr;
	class Control* control = nullptr;
	vector<AnimationClip*> clips;
	int point = 0;
	bool hit = false;
	int HP = 3;
	int hitAnimPoint = 2;

	bool is_Death = false;

	float hitTime = 0.0f;
	float hitSafeTime = 2.0f;

	float twinklingTime = 0.0f;
	float twinklingdelay = 0.1f;

	// Character을(를) 통해 상속됨
};