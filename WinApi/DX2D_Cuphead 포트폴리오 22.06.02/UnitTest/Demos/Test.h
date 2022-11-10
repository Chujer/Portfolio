#pragma once

enum GameState {
	GAME_INTRO = 0,
	PLAY = 1,
	END = 2
};

class Test :public IObject
{
public:
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

	bool ObbCharacterCheck(Character* a, Character* b)
	{
		return OBB::CheckIntersect(a->GetAnimRect()->GetObb(), b->GetAnimRect()->GetObb());
	}

	bool ObbBulletCheck(Bullet* a, Character* b)
	{
		return OBB::CheckIntersect(a->GetAnimRect()->GetObb(),b->GetAnimRect()->GetObb());
	}
	
private:
	class Mob_Potato* hitbox = nullptr;
	class Mob_Onion* hitbox2 = nullptr;
	class Mob_Carrot* hitbox3 = nullptr;
	class Player* player = nullptr;

	class Effect* ground = nullptr;
	class Effect* ground2 = nullptr;
	class Effect* hpUI = nullptr;

	class Effect* log = nullptr;

	int gameInfo = GAME_INTRO;

	int bulletCount = 0;
	
	/*class AnimationRect* ch;
	class Animator* animator;
	class AnimationClip* clips;*/
};

