#include "Framework.h"
#include "Mob_Potato.h"

Mob_Potato::Mob_Potato(Vector3 position, Vector3 size, HitBox* target, bool active = false)
	:Character(position, size)
{
	state = INTRO;
	hitbox = new HitBox({ 930, 120, 0 }, { 300, 430, 1 }, "Mob");

	this->target = target;

	Texture2D* srcTex = new Texture2D(TexturePath + L"/Monster/Potato/Potato.png");

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	bullet[0] = new Bullet({ 800,180,0 }, { 130,130,1 }, 4.5f, L"Potato_Bullet");
	bullet[1] = new Bullet({ 800,180,0 }, { 130,130,1 }, 4.5f, L"Potato_Bullet");
	bullet[2] = new Bullet({ 800,180,0 }, { 130,130,1 }, 4.5f, L"Potato_Bullet");
	bullet[3] = new Bullet({ 800,180,0 }, { 130,130,1 }, 4.5f, L"Potato_P_Bullet");

	float scsizeX = texSize.x / 18.0f;
	float scsizeY = texSize.y / 4.0f;

	clips.push_back(new AnimationClip(L"Intro", srcTex, 18, Vector2(0, 0), Vector2(scsizeX * 18, scsizeY), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Idle", srcTex, 9, Vector2(0, scsizeY), Vector2(scsizeX * 9, scsizeY * 2), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Attack", srcTex, 17, Vector2(0, scsizeY * 2), Vector2(scsizeX * 17, scsizeY * 3), 1.0f / attackSpeed));
	clips.push_back(new AnimationClip(L"Death", srcTex, 18, Vector2(0, scsizeY * 3), Vector2(scsizeX * 18, scsizeY * 4), 1.0f / 22.0f));
	
	animator->AddAnimClips(clips);

	animator->SetCurrentAnimClip(L"Death");

	animRect->SetAnimation(animator);
	this->active = active;

}

Mob_Potato::~Mob_Potato()
{
	SAFE_DELETE(ground);
	SAFE_DELETE(ground2);
	SAFE_DELETE(hitbox);
	for (AnimationClip* c : clips)
	{
		SAFE_DELETE(c);
	}
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(bullet[i]);
	}
}

void Mob_Potato::Update()
{
	if (HP < 0)
	{
		state = DEATH;
		isDeath = true;
	}
	else if (HP < 100)
		attackSpeed = 33.0f;
	else if (HP < 200)
		attackSpeed = 27.0f;
	else if (HP < 300)
		attackSpeed = 22.0f;


	animator->Update();
	animRect->Update();
	if (ground != nullptr)
	{
		ground->Update();
		ground2->Update();
	}
	hitbox->Update();

	if (state == INTRO)
	{
		if (animator->GetEndAni(L"Intro"))
		{
			ground = new Effect({ 680,60,0 }, { 850,150,1 }, L"Ground1");
			ground2 = new Effect({ 700,60,0 }, { 750,150,1 }, L"Ground2");
			state = IDLE;
		}
		animator->SetCurrentAnimClip(L"Intro");
	}
	else if (state == IDLE)
	{
		if (GetLoopEnd())
		{
			state = ATTACK;
		}
		if(state==IDLE)
			loopAnimation(3, L"Idle");
	}
	else if (state == ATTACK)
	{
		if (animator->GetFrameAni(L"Attack",13))
		{
			bullet[bulletIndex]->SetActive(true);
			bulletIndex++;
			if (bulletIndex > 3)
				bulletIndex = 0;
		}
		if (GetLoopEnd())
		{
			animator->SetAnimationSpeed(L"Attack", 1.0f / attackSpeed);
			state = IDLE;
		}
		if(state == ATTACK)
			loopAnimation(4, L"Attack");
	}
	else if (state == DEATH)
	{
		if(animator->GetClipName() != L"Death")
			loopCount = -1;

		if (GetLoopEnd())
		{
			goNextMob = true;
			active = false;
		}
		loopAnimation(3, L"Death");
	}

}

void Mob_Potato::Render()
{
	sb->SetPoint(point);
	sb->SetPSBuffer(0);
	if (ground != nullptr)
		ground->Render();
	animRect->Render();
	hitbox->Render();
	if (ground != nullptr)
		ground2->Render();

	for (int i = 0; i < 4; i++)
	{
		if(bullet[i]->GetActive()==true)
			bullet[i]->Update();
	}
}

void Mob_Potato::Move()
{
}

void Mob_Potato::AABB(Character * other)
{
}

bool Mob_Potato::OBB()
{
	for (int i = 0; i < 4; i++)
	{
		if (OBB::CheckIntersect(bullet[i]->GetHitBox()->GetAnimRect()->GetObb(), target->GetAnimRect()->GetObb()) && bullet[i]->GetActive() == true)
		{
			bullet[i]->SetPotatoBulletPosition();
			return true;
		}
	}
	return false;

}


void Mob_Potato::SetActive(bool active)
{
	this->active = active;
}

void Mob_Potato::loopAnimation(int count, wstring name)
{
	if (loopCount < count)
	{
		if (animator->GetEndAni(animator->GetClipName()) == true || loopCount == -1)
		{
			animator->SetCurrentAnimClip(name);
			loopCount++;
		}
	}
	else if (loopCount == count)
	{
		loopCount = -1;
		loopEnd = true;
	}
}

bool Mob_Potato::GetActive()
{
	return active;
}
