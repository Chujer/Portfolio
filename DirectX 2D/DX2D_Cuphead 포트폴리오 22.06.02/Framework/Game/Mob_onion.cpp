#include "Framework.h"
#include "Mob_Onion.h"

Mob_Onion::Mob_Onion(Vector3 position, Vector3 size, HitBox* target, bool active = false)
	:Character(position, size)
{
	srand((unsigned)time(NULL));
	hitbox = new HitBox({ 470, 80, 0 }, { 370, 430, 1 }, "Mob");
	introGround = new Effect({ 300,-10,0 }, { 750,550,1 }, L"IntroGround");
	tear_L = new Effect({ -8,400,0 }, { 640,450,1 }, L"Tear_Intro_L");
	tear_R = new Effect({ 660,400,0 }, { 640,450,1 }, L"Tear_Intro_R");

	this->target = target;

	//ground = new Effect({ 720,60,0 }, { 750,150,1 }, L"Ground1");
	Texture2D* srcTex = new Texture2D(TexturePath + L"/Monster/Onion/Onion.png");

	LeftTear[0] = new Bullet({ (float)20 + (rand() % 430), (float)780 + (rand() % 200), 0 }, { 220,150,1 }, 5.0f, L"Onion_Bullet_L");
	LeftTear[1] = new Bullet({ (float)20 + (rand() % 430), (float)780 + (rand() % 200), 0 }, { 220,150,1 }, 5.0f, L"Onion_Bullet_L");
	LeftTear[2] = new Bullet({ (float)20 + (rand() % 430), (float)780 + (rand() % 200), 0 }, { 220,150,1 }, 5.0f, L"Onion_P_Bullet_L");
	LeftTear[3] = new Bullet({ (float)20 + (rand() % 430), (float)780 + (rand() % 200), 0 }, { 220,150,1 }, 5.0f, L"Onion_Bullet_L");

	RightTear[0] = new Bullet({ (float)865 + (rand() % 395), (float)780 + (rand() % 200), 0 }, { 220,150,1 }, 5.0f, L"Onion_Bullet_R");
	RightTear[1] = new Bullet({ (float)865 + (rand() % 395), (float)780 + (rand() % 200), 0 }, { 220,150,1 }, 5.0f, L"Onion_Bullet_R");
	RightTear[2] = new Bullet({ (float)865 + (rand() % 395), (float)780 + (rand() % 200), 0 }, { 220,150,1 }, 5.0f, L"Onion_P_Bullet_R");
	RightTear[3] = new Bullet({ (float)865 + (rand() % 395), (float)780 + (rand() % 200), 0 }, { 220,150,1 }, 5.0f, L"Onion_Bullet_R");
	
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	state = INTRO;
	float scsizeX = texSize.x / 32.0f;
	float scsizeY = texSize.y / 8.0f;

	clips.push_back(new AnimationClip(L"Intro", srcTex, 24, Vector2(0, 0), Vector2(scsizeX*24.0f, scsizeY), 1.0f / 10.0f));
	clips.push_back(new AnimationClip(L"Idle", srcTex, 21, Vector2(0, scsizeY), Vector2(scsizeX*21.0f, scsizeY*2.0f), 1.0f / 20.0f));
	clips.push_back(new AnimationClip(L"Cry_Ready", srcTex, 10, Vector2(0, scsizeY*2.0f), Vector2(scsizeX*10.0f, scsizeY*3.0f), 1.0f / 18.0f));
	clips.push_back(new AnimationClip(L"Cry_On", srcTex, 8, Vector2(0, scsizeY*3.0f), Vector2(scsizeX*8.0f, scsizeY*4.0f), 1.0f / 18.0f));		//cry 부분 수정 필요
	clips.push_back(new AnimationClip(L"Cry_Loop", srcTex, 15, Vector2(0, scsizeY*4.0f), Vector2(scsizeX*15.0f, scsizeY*5.0f), 1.0f / 18.0f));		//cry 부분 수정 필요
	clips.push_back(new AnimationClip(L"Cry_End", srcTex, 9, Vector2(0, scsizeY*5.0f), Vector2(scsizeX*9.0f, scsizeY*6.0f), 1.0f / 18.0f));
	clips.push_back(new AnimationClip(L"Death", srcTex, 12, Vector2(0, scsizeY*6.0f), Vector2(scsizeX*12.0f, scsizeY*7.0f), 1.0f / 18.0f));
	clips.push_back(new AnimationClip(L"DeathLeave", srcTex, 32, Vector2(0, scsizeY*7.0f), Vector2(scsizeX*32.0f, scsizeY*8.0f), 1.0f / 18.0f));

	animator->AddAnimClips(clips);

	animator->SetCurrentAnimClip(L"Intro");

	animRect->SetAnimation(animator);
	this->isActive = active;

}

Mob_Onion::~Mob_Onion()
{
	SAFE_DELETE(hitbox);
	SAFE_DELETE(introGround);
	for (AnimationClip* c : clips)
	{
		SAFE_DELETE(c);
	}
	SAFE_DELETE(tear_L);
	SAFE_DELETE(tear_R);
}

void Mob_Onion::Update()
{
	animator->Update();
	animRect->Update();
	hitbox->Update();
	introGround->Update();

	if (HP < 100)
		loopAniCount = 6;
	else if (HP < 200)
		loopAniCount = 5;
	else if (HP < 300)
		loopAniCount = 4;

	if (state != DEATH && state != DEATH_LEAVE)
	{
		if (HP < 0)
		{
			state = DEATH;
			tear_L->GetAnimator()->SetCurrentAnimClip(L"Tear_End_L");
			tear_R->GetAnimator()->SetCurrentAnimClip(L"Tear_End_R");	
			isDeath = true;
		}		
	}

	if (tear_On == true)
	{
		tear_L->Update();
		tear_R->Update();
	}
	if (introGround->GetAnimator()->GetEndAni(L"IntroGround"))
	{
		introGround = new Effect({ 280,40,0 }, { 750,160,1 }, L"Ground1");
	}

	if (tear_L->GetAnimator()->GetEndAni(L"Tear_End_L"))
		tear_On = false;

	if (state == INTRO)
	{
		if (animator->GetEndAni(L"Intro"))
			state = IDLE;

		animator->SetCurrentAnimClip(L"Intro");
	}
	else if (state == IDLE)
	{
		if (animator->GetEndAni(L"Idle"))
			state = ATTACK_READY;

		animator->SetCurrentAnimClip(L"Idle");
	}
	else if (state == ATTACK_READY)
	{
		if (animator->GetEndAni(L"Cry_Ready"))
			state = ATTACK_ON;

		animator->SetCurrentAnimClip(L"Cry_Ready");
	}
	else if (state == ATTACK_ON)
	{
		if (animator->GetEndAni(L"Cry_On"))
		{
			tear_L->GetAnimator()->SetCurrentAnimClip(L"Tear_Intro_L");
			tear_R->GetAnimator()->SetCurrentAnimClip(L"Tear_Intro_R");
			state = ATTACK_LOOP;
			tear_On = true;
		}
		if(animator->GetClipName()!=L"Cry_On")
			animator->SetCurrentAnimClip(L"Cry_On");
	}
	else if (state == ATTACK_LOOP)
	{
		if (animator->GetClipName() != L"Cry_Loop")
			loopCount = -1;
		if (GetLoopEnd())
		{
			state = ATTACK_END;
		}

		attackTime += Time::Delta();
		if (attackTime > attackDelayTime)
		{
			if ((rand() % 100) < 51)
			{
				LeftTear[tearLIndex]->SetOnionBulletPosition();
				LeftTear[tearLIndex]->SetActive(true);
				tearLIndex++;
				if (tearLIndex > 3)
					tearLIndex = 0;
			}
			else
			{
				RightTear[tearLIndex]->SetOnionBulletPosition();
				RightTear[tearRIndex]->SetActive(true);
				tearRIndex++;
				if (tearRIndex > 3)
					tearRIndex = 0;
			}
			attackTime = 0.0f;
		}
		loopAnimation(loopAniCount, L"Cry_Loop");
		//animator->SetCurrentAnimClip(L"Cry_Loop");
	}
	else if (state == ATTACK_END)
	{
		if (animator->GetEndAni(L"Cry_End"))
			state = ATTACK_READY;
		if (state == ATTACK_END)
		{
			tear_L->GetAnimator()->SetCurrentAnimClip(L"Tear_End_L");
			tear_R->GetAnimator()->SetCurrentAnimClip(L"Tear_End_R");
			animator->SetCurrentAnimClip(L"Cry_End");
		}
	}
	else if (state == DEATH)
	{
		if (animator->GetClipName() != L"Death")
			loopCount = -1;
		isDeath = true;
		if (GetLoopEnd())
		{
			state = DEATH_LEAVE;
		}
		loopAnimation(4, L"Death");
	}
	else if (state == DEATH_LEAVE)
	{
		if (animator->GetEndAni(L"DeathLeave"))
		{
			isActive = false;
			goNextMob = true;
		}
		animator->SetCurrentAnimClip(L"DeathLeave");
	}

}

bool Mob_Onion::GetActive()
{
	return isActive;
}
void Mob_Onion::SetActive(bool active)
{
	this->isActive = active;
}

void Mob_Onion::Render()
{
	sb->SetPoint(point);
	sb->SetPSBuffer(0);

	animRect->Render();
	hitbox->Render();
	introGround->Render();
	if (tear_On == true)
	{
		tear_L->Render();
		tear_R->Render();
	}

	for (int i = 0; i < 4; i++)
	{
		if (LeftTear[i]!=nullptr)
		{
			LeftTear[i]->Update();
		}
		if (RightTear[i]!= nullptr)
		{
			RightTear[i]->Update();
		}
	}
}

void Mob_Onion::Move()
{
}


void Mob_Onion::loopAnimation(int count, wstring name)
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
//path == L"Onion_Bullet_L" || path == L"Onion_Bullet_R"
//|| path == L"Onion_P_Bullet_L" || path == L"Onion_P_Bullet_R"
bool Mob_Onion::OBB()
{
	for (int i = 0; i < 4; i++)
	{
		if (OBB::CheckIntersect(LeftTear[i]->GetHitBox()->GetAnimRect()->GetObb(), target->GetAnimRect()->GetObb()) && LeftTear[i]->GetActive() == true
			&& LeftTear[i]->GetAnimRect()->GetAnimator()->GetClipName()== L"Onion_Bullet")
		{
			printf("양파 왼쪽눈물");
			LeftTear[i]->GetAnimRect()->GetAnimator()->SetCurrentAnimClip(L"Onion_Bullet_Broken");
			LeftTear[i]->SetActive(false);
			return true;
		}
		if (OBB::CheckIntersect(RightTear[i]->GetHitBox()->GetAnimRect()->GetObb(), target->GetAnimRect()->GetObb()) && RightTear[i]->GetActive() == true
			&& RightTear[i]->GetAnimRect()->GetAnimator()->GetClipName() == L"Onion_Bullet")
		{
			printf("양파 왼쪽눈물");
			RightTear[i]->GetAnimRect()->GetAnimator()->SetCurrentAnimClip(L"Onion_Bullet_Broken");
			RightTear[i]->SetActive(false);
			return true;
		}
	}
	return false;
}
