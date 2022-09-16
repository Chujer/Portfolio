#include "Framework.h"
#include "Mob_Carrot.h"
#include "Effect.h"
#include "Bullet.h"
Mob_Carrot::Mob_Carrot(Vector3 position, Vector3 size, HitBox* target, bool Active = false)
	:Character(position, size)
{
 	hitbox = new HitBox({ 550, 500, 0 }, { 190, 130, 1 }, "Mob");
	ground = new Effect({ 0,0,0 }, { WinMaxWidth,WinMaxHeight,1 }, L"BackGround");

	this->target = target;

	missile[0] = new Bullet({ 0,780,0 }, { 75,130,1 }, 1.0f, L"Carrot_Missile");
	missile[1] = new Bullet({ 200,780,0 }, { 75,130,1 }, 1.0f, L"Carrot_Missile");
	missile[2] = new Bullet({ 400,780,0 }, { 75,130,1 }, 1.0f, L"Carrot_Missile");
	missile[3] = new Bullet({ 600,780,0 }, { 75,130,1 }, 1.0f, L"Carrot_Missile");
	missile[4] = new Bullet({ 720 ,780,0 }, { 75,130,1 }, 1.0f, L"Carrot_Missile");

	beamEffect = new Effect({ 495,495,0 }, { 300,300,1 }, L"Beam_Effect");

	beam[0] = new Bullet({ 640,630,0 }, { 160,160,1 }, 1.0f, L"Carrot_Beam");
	beam[1] = new Bullet({ 640,630,0 }, { 160,160,1 }, 1.0f, L"Carrot_Beam");
	beam[2] = new Bullet({ 640,630,0 }, { 160,160,1 }, 1.0f, L"Carrot_Beam");
	beam[3] = new Bullet({ 640,630,0 }, { 160,160,1 }, 1.0f, L"Carrot_Beam");
	for (int i = 0; i < 5; i++)
	{
		beam[i]->SetTarget(target);
		if (i < 5)
			missile[i]->SetTarget(target);
	}

	Texture2D* srcTex = new Texture2D(TexturePath + L"/Monster/Carrot/Carrot.png");

	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	state = INTRO;
	float scsizeX = texSize.x / 24.0f;
	float scsizeY = texSize.y / 6.0f;

	clips.push_back(new AnimationClip(L"Intro", srcTex, 24, Vector2(0, 0), Vector2(scsizeX * 24.0f, scsizeY), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Intro2", srcTex, 9, Vector2(0, scsizeY), Vector2(scsizeX * 9.0f, scsizeY*2.0f), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Attack1", srcTex, 23, Vector2(0, scsizeY*2.0f), Vector2(scsizeX * 23.0f, scsizeY * 3.0f), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Attack2R", srcTex, 10, Vector2(0, scsizeY * 3.0f), Vector2(scsizeX * 10.0f, scsizeY * 4.0f), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Attack2", srcTex, 6, Vector2(0, scsizeY * 4.0f), Vector2(scsizeX * 6.0f, scsizeY * 5.0f), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Death", srcTex, 24, Vector2(0, scsizeY * 5.0f), Vector2(scsizeX*24.0f, scsizeY * 6.0f), 1.0f / 22.0f));

	animator->AddAnimClips(clips);

	animator->SetCurrentAnimClip(L"Intro");
	

	animRect->SetAnimation(animator);
	this->isActive = Active;
}

Mob_Carrot::~Mob_Carrot()
{
	SAFE_DELETE(hitbox);
	SAFE_DELETE(beamEffect);
	for (int i = 0; i < 5 ; i++)
	{
		SAFE_DELETE(missile[i]);
		if(i<4)
			SAFE_DELETE(beam[i]);
	}
	for (AnimationClip* c : clips)
	{
		SAFE_DELETE(c);
	}
	SAFE_DELETE(ground);
}

void Mob_Carrot::Update()
{
	animator->Update();
	animRect->Update();
	hitbox->Update();

	if (HP < 0)
		state = DEATH;

	if (HP < 100)
	{
		loopAniCount_Missile = 7;
	}
	else if (HP < 200)
		loopAniCount_Missile = 5;
	else if (HP < 300)
		loopAniCount_Missile = 4;

	if (state == INTRO)
	{
		if (animator->GetEndAni(L"Intro"))
		{
			state = INTRO2;
		}
		else if(animator->GetClipName()!=L"Intro2")
			animator->SetCurrentAnimClip(L"Intro");
	}

	if (state == INTRO2)
	{
		if (animator->GetEndAni(L"Intro2"))
			state = ATTACK;
		else if (animator->GetClipName() != L"Attack1")
			animator->SetCurrentAnimClip(L"Intro2");
	}

	else if (state == ATTACK)
	{
		if (animator->GetClipName() != L"Attack1")
			loopCount = -1;

		if (GetLoopEnd())
			state = ATTACK2R;

		if(state==ATTACK)
			loopAnimation(loopAniCount_Missile, L"Attack1");

		missileTime += Time::Delta();

		if (missileTime > missileDelayTime)
		{
			if (missile[missileIndex]->GetActive() == false)
			{
				missile[missileIndex]->SetActive(true);
				missileIndex++;
			}
			if (missileIndex == 5)
				missileIndex = 0;
			missileTime = 0;
		}
	}

	else if (state == ATTACK2R)
	{
		if (animator->GetEndAni(L"Attack2R"))
		{
			state = ATTACK2;
			beamOn=true;
		}

		if (state==ATTACK2R)
			animator->SetCurrentAnimClip(L"Attack2R");
	}

	else if (state == ATTACK2)		// 패턴의 타이밍을 애니메이션이아닌 시간을 기점으로 설정함
	{
		attack2Time += Time::Delta();
		beamShootTime += Time::Delta();

		if (beamOn == true)
		{
			if (beamEffect->GetAnimator()->GetFrameAni(L"Beam_Effect",7))		//빔 이펙트를 2번사용
			{
				effectLoop++;
			}
			if (effectLoop == 2)				//빔이펙트가 2번째가 되었을때 플레이어 위치 잡기
			{
				beamOn = false;
				onBeamTime = true;
				effectLoop = 0;
				targetPosition = target->GetPosition();
			}
		}

		if (onBeamTime == true)		//빔이 발사되는 순간
		{
			beamTime += Time::Delta();
			if (beamTime > beamDelayTime)
			{
				beam[beamIndex]->SetTargetPosition(targetPosition);
				beam[beamIndex]->SetActive(true);
				beamIndex++;
				if (beamIndex == 4)
				{
					beamIndex = 0;
					onBeamTime = false;
				}
				beamTime = 0;
			}
		}

		if (beamShootTime>beamShootDelayTime)
		{
			beamOn = true;
			beamShootTime = 0.0f;
		}

		if (attack2Time > attack2CountinuingTime)
		{
			attack2Time = 0.0f;
			beamShootTime = 0.0f;
			state = ATTACK;
		}

		if(state == ATTACK2)
			animator->SetCurrentAnimClip( L"Attack2");
	}

	else if (state == DEATH)
	{
		beamOn = false;
		if (DeathAniCount>3)
		{
			isDeath = true;
			isActive = false;
		}
		if (isDeath == false)
		{
			animator->SetCurrentAnimClip(L"Death");
			DeathAniCount++;
		}

	}

	if(beamOn == true)
		beamEffect->Update();

	
	ground->Update();
}

void Mob_Carrot::Render()
{
	sb->SetPoint(point);
	sb->SetPSBuffer(0);

	animRect->Render();
	hitbox->Render();
	ground->Render();
	if (beamOn == true)
		beamEffect->Render();

	for (int i = 0; i < 5; i++)
	{
		if (missile[i]->GetActive())
			missile[i]->Update();
		if (i < 4 && beam[i]->GetActive())
			beam[i]->Update();
	}
}

void Mob_Carrot::Move()
{
}

bool Mob_Carrot::GetActive()
{
	return isActive;
}

void Mob_Carrot::SetActive(bool active)
{
	this->isActive = active;
}

void Mob_Carrot::loopAnimation(int count, wstring name)
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

bool Mob_Carrot::OBB()
{
	for (int i = 0; i < 5; i++)
	{
		if (OBB::CheckIntersect(missile[i]->GetHitBox()->GetAnimRect()->GetObb(), target->GetAnimRect()->GetObb()) && missile[i]->GetActive()==true)
		{
			missile[i]->SetCarrotBulletPosition();
			//missile[i]->SetActive(false);
			return true;
		}
	}
	
	for (int j = 0; j < 4; j++)
	{
		if (OBB::CheckIntersect(beam[j]->GetHitBox()->GetAnimRect()->GetObb(), target->GetAnimRect()->GetObb()) && beam[j]->GetActive() == true&&beam[j]->GetAnimRect()->GetAnimator()->GetClipName()== L"Carrot_Beam")
		{
			return true;
		}
	}
	return false;
}
