#pragma once
#include "Character.h"
#include "Game/Effect.h"
#include "Game/Bullet.h"

class Mob_Onion: public Character
{
	public:
		Mob_Onion(Vector3 position, Vector3 size, HitBox* target, bool Active);
		~Mob_Onion();
		virtual void Update() override;
		virtual void Render() override;
		virtual void Move() override;
		virtual bool GetActive() override;
		virtual void SetActive(bool active) override;


		void Hit(int damage) { HP = HP - damage; }
		bool GetIsDeath() { return isDeath; }
		HitBox* GetHitBox() { return hitbox; }

		void SetHp() { HP = HP - 101; }
		bool GetNextMob() { return goNextMob; }

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
		AnimationRect* GetAnimRect() { return animRect; }

	private:
		class HitBox* target = nullptr;
		class HitBox* hitbox = nullptr;
		class Effect* introGround = nullptr;
		class Effect* tear_L = nullptr;
		class Effect* tear_R = nullptr;
		class Effect* ground = nullptr;
		vector<AnimationClip*> clips;
		class Bullet* LeftTear[4];
		class Bullet* RightTear[4];

		int loopCount = -1;
		bool loopEnd = false;
		int state;
		int HP = 400;

		bool goNextMob = false;

		int point = -1;
		bool isDeath = false;
		bool isActive = false;
		bool tear_On = false;
		int tearLIndex = 0;
		int tearRIndex = 0;
		int loopAniCount = 3;

		float attackTime = 0.0f;
		float attackDelayTime = 0.8f;
};

