#include "Framework.h"
#include "Bullet.h"
#define _USE_MATH_DEFINES
#include <math.h>

Bullet::Bullet(Vector3 position, Vector3 size, float speed, wstring path, float rotation)
{
	srand((unsigned)time(NULL));
	tex = new AnimationRect(position, size, true);
	animator = new Animator;
	tex->SetRotation(rotation);
	this->speed = speed;
	respawn = position;
	sb = new ShadedBuffer();
	//wcout <<endl<< (*position).x<<" "<< (*position).y << " " << (*position).z<<endl;

	if (path == TexturePath + L"Bullet.png" || path == TexturePath + L"Bullet2.png")
	{
		SetPlayerBullet(path);
	}
	else if (path == L"Potato_Bullet"||path==L"Potato_P_Bullet")
	{
		SetPotatoBullet(path);
		hitBoxRespawn = position - Vector3(45.0f, 50.0f, 0);
		hitBoxSize = size / 1.5f;
		hitbox = new HitBox(hitBoxRespawn, hitBoxSize, "Bullet");
	}
	else if (path == L"Onion_Bullet_L" || path == L"Onion_Bullet_R" 
			|| path == L"Onion_P_Bullet_L" || path == L"Onion_P_Bullet_R" )
	{
		SetOnionBullet(path);
		hitBoxRespawn = position - Vector3(25.0f, 35.0f, 0);
		hitBoxSize = Vector3(45.0f, 75.0f, 0);
		hitbox = new HitBox(hitBoxRespawn, hitBoxSize, "Bullet");
	}
	else if (path == L"Carrot_Missile" || path == L"Carrot_Beam")
	{
		SetCarrotBullet(path);
		if (path == L"Carrot_Missile")
		{
			hitBoxRespawn = position;
			hitBoxSize = size - Vector3(20.0f,10.0f,0);
			hitbox = new HitBox(hitBoxRespawn, hitBoxSize, "Bullet");
			hitbox->SetReHitBox(hitBoxRespawn, hitBoxSize, true);
		}
		else
		{
			hitBoxRespawn = position;
			hitBoxSize = size/1.2f;
			hitbox = new HitBox(hitBoxRespawn, hitBoxSize, "Bullet");
			hitbox->SetReHitBox(hitBoxRespawn, hitBoxSize, true);
		}
	}
}

Bullet::~Bullet()
{
	SAFE_DELETE(tex);
	SAFE_DELETE(animator);
	SAFE_DELETE(clip);
	for (AnimationClip* c : clips)
		SAFE_DELETE(c);
	SAFE_DELETE(bulletDeathAni);
	SAFE_DELETE(hitbox);
}

void Bullet::Update()
{
	dathTime += Time::Delta();

	if (animname == TexturePath + L"Bullet.png" || animname == TexturePath + L"Bullet2.png")
	{
		PlayerBulletUpdate();
	}
	else if (animname == L"Potato_Bullet" || animname == L"Potato_P_Bullet")
	{
		PotatoBulletUpdate();
	}
	else if (animname == L"Onion_Bullet_L" || animname == L"Onion_Bullet_R"
		|| animname == L"Onion_P_Bullet_L" || animname == L"Onion_P_Bullet_R")
	{
		OnionBulletUpdate();
	}
	else if (animname == L"Carrot_Missile")
	{
		UpdateData();
		CarrotBulletUpdate();
	}
	else if (animname == L"Carrot_Beam" || animname == L"Carrot_Beam_Ready")
	{
		CarrotBeamUpdate();
	}

	if (bulletDeathAni != nullptr && bulletDeathAni->GetActive())
	{
		bulletDeathAni->Update();
		bulletDeathAni->Render();
	}
	if (bulletDeathAni != nullptr && bulletDeathAni->GetActive() && bulletDeathAni->GetAnimator()->GetEndAni(L"BulletDeath"))
	{
		bulletDeathAni->SetActive(false);
	}

	if (active == true)
	{
		sb->SetPoint(0);
		sb->SetPSBuffer(0);
		tex->Update();
		tex->Render();
		animator->Update();
		if (hitbox != nullptr)
		{
			hitbox->Update();
			hitbox->Render();
		}
	}
}
void Bullet::SetActive(bool active)
{
	this->active = active;
}

void Bullet::SetPlayerBullet(wstring path)
{
	animname = path;
	damage = 3;
	mode = 0;
	active = true;
	bulletDeathAni = new Effect(Vector3(200,200,1), Vector3(200, 200, 1), L"BulletDeath");
	bulletDeathAni->ChangeEffect(Vector3(200, 200, 1), Vector3(200, 200, 1),true);
	bulletDeathAni->SetActive(false);

	Texture2D* srcTex = new Texture2D(TexturePath + L"Bullet.png");
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"Bullet2.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	Vector2 texSize2 = Vector2(srcTex2->GetWidth(), srcTex2->GetHeight());
	clips.push_back(new AnimationClip(L"Bullet", srcTex, 1, Vector2(0, 0), texSize, 1.0f / 10.0f));
	clips.push_back(new AnimationClip(L"Bullet2", srcTex2, 1, Vector2(0, 0), texSize2, 1.0f / 10.0f));
	animator->AddAnimClips(clips);
	animator->SetCurrentAnimClip(L"Bullet");
	tex->SetAnimation(animator);
}

void Bullet::SetPlayerBulletInfo(Vector3 position, float rotation, wstring path)
{
	tex->SetPosition(position);
	tex->SetRotation(rotation);
	this->animname = path;
	animator->SetCurrentAnimClip(path);

	if (path == TexturePath + L"Bullet.png")
		animator->SetCurrentAnimClip(L"Bullet");
	else
		animator->SetCurrentAnimClip(L"Bullet2");

	tex->Update();
	active = true;
}


void Bullet::SetPotatoBullet(wstring path)
{
	animname = path;
	damage = 1;
	mode = 0;
	Texture2D* srcTex = new Texture2D(TexturePath + L"Monster/Potato/Bullet/Bullet.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	float scsizeX = texSize.x / 8.0f;
	float scsizeY = texSize.y / 2.0f;
	if (path == L"Potato_Bullet")
	{
		clip = new AnimationClip(L"Potato_Bullet", srcTex, 8, Vector2(0, 0), Vector2(scsizeX * 8.0f, scsizeY), 1.0f / 22.0f);
	}
	else if (path == L"Potato_P_Bullet")
	{
		isParry = true;
		clip = new AnimationClip(L"Potato_Bullet", srcTex, 4, Vector2(0, scsizeY), Vector2(scsizeX * 4.0f, scsizeY * 2.0f), 1.0f / 22.0f);
	}
	animator->AddAnimClips(clip);
	animator->SetCurrentAnimClip(L"Potato_Bullet");
	tex->SetAnimation(animator);
}

void Bullet::SetPotatoBulletPosition()
{
	tex->SetPosition(respawn);
	hitbox->GetAnimRect()->SetPosition(hitBoxRespawn);
	active = false;
	//tex->GetAnimator()->Update();
}

void Bullet::SetOnionBullet(wstring path)
{
	animname = path;
	damage = 1;
	mode = 0;
	Texture2D* srcTex = new Texture2D(TexturePath + L"Monster/Onion/Bullet/Bullet.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());

	float scsizeX = texSize.x / 7.0f;
	float scsizeY = texSize.y / 4.0f;

	if (path == L"Onion_Bullet_L"||path == L"Onion_Bullet_R")
	{
		clips.push_back( new AnimationClip(L"Onion_Bullet", srcTex, 3, Vector2(0, 0), Vector2(scsizeX * 3.0f, scsizeY), 1.0f / 22.0f));
		clips.push_back(new AnimationClip(L"Onion_Bullet_Broken", srcTex, 7, Vector2(0, scsizeY), Vector2(scsizeX * 7.0f, scsizeY*2.0f), 1.0f / 22.0f));
	}
	else if (path == L"Onion_P_Bullet_L" || path == L"Onion_P_Bullet_R")
	{
		isParry = true;
		clips.push_back(new AnimationClip(L"Onion_Bullet", srcTex, 3, Vector2(0, scsizeY * 2.0f), Vector2(scsizeX * 3.0f, scsizeY * 3.0f), 1.0f / 22.0f));
		clips.push_back(new AnimationClip(L"Onion_Bullet_Broken", srcTex, 6, Vector2(0, scsizeY * 3.0f), Vector2(scsizeX * 6.0f, scsizeY * 4.0f), 1.0f / 22.0f));
	}
	animator->AddAnimClips(clips);
	animator->SetCurrentAnimClip(L"Onion_Bullet");
	tex->SetAnimation(animator);
}

void Bullet::SetOnionBulletPosition(bool isLeft)
{

}

void Bullet::SetCarrotBullet(wstring path)
{

	animname = path;
	damage = 1;
	mode = 0;
	Texture2D* srcTex = new Texture2D(TexturePath + L"Monster/Carrot/Bullet/Bullet.png");
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"Monster/Carrot/Bullet/Bullet_Beam.png");
	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
	Vector2 texSize2 = Vector2(srcTex2->GetWidth(), srcTex2->GetHeight());

	float scsizeX = texSize2.x / 6.0f;
	float scsizeY = texSize2.y / 2.0f;

	if (path == L"Carrot_Missile")
	{
		clip = new AnimationClip(L"Carrot_Missile", srcTex, 1, Vector2(0, 0), texSize, 1.0f / 1.0f);
		animator->AddAnimClips(clip);
		animator->SetCurrentAnimClip(L"Carrot_Missile");
	}
	else if (path == L"Carrot_Beam")
	{
		clips.push_back(new AnimationClip(L"Carrot_Beam_Ready", srcTex2, 6, Vector2(0, 0), Vector2(scsizeX * 6.0f, scsizeY), 1.0f / 22.0f));
		clips.push_back(new AnimationClip(L"Carrot_Beam", srcTex2, 6, Vector2(0, scsizeY), Vector2(scsizeX * 6.0f, scsizeY * 2.0f), 1.0f / 22.0f));
		animator->AddAnimClips(clips);
		animator->SetCurrentAnimClip(L"Carrot_Beam_Ready");
	}
	tex->SetAnimation(animator);
}

void Bullet::SetCarrotBulletPosition()
{
	randPosition = Vector3(rand() % 720, 780, 0);
	tex->SetPosition(randPosition);
	hitbox->GetAnimRect()->SetPosition(randPosition);
	active = false;
	hp = 12;
}

void Bullet::SetOnionBulletPosition()
{
	
	if (animname == L"Onion_Bullet_L" || animname == L"Onion_P_Bullet_L")
	{
		randPosition = Vector3(20.0f + (rand() % 430), 700.0f + (rand() % 100), 0);
		tex->SetPosition(randPosition);
		hitbox->GetAnimRect()->SetPosition(randPosition - Vector3(25.0f, 35.0f, 0));
	}
	else if (animname == L"Onion_Bullet_R" || animname == L"Onion_P_Bullet_R")
	{
		randPosition = Vector3(865.0f + (rand() % 395), 700.0f + (rand() % 100), 0);
		tex->SetPosition(randPosition);
		hitbox->GetAnimRect()->SetPosition(randPosition - Vector3(25.0f, 35.0f, 0));
	}
	animator->SetCurrentAnimClip(L"Onion_Bullet");
}


void Bullet::PlayerBulletUpdate()
{
	if (dathTime > 2.0f)
	{
		dath = true;
	}
	if (tex->GetRotation() == 0.0f)
	{
		if (animname == TexturePath + L"Bullet.png")
			tex->SetPosition(*tex->GetPosition() + Vector3(speed, 0, 0));
		else if (animname == TexturePath + L"Bullet2.png")
			tex->SetPosition(*tex->GetPosition() - Vector3(speed, 0, 0));
	}
	else if (tex->GetRotation() == 45.0f)
	{
		if (animname == TexturePath + L"Bullet.png")
		{
			tex->SetPosition(*tex->GetPosition() + Vector3(speed, speed, 0));
		}

		else if (animname == TexturePath + L"Bullet2.png")
		{
			tex->SetPosition(*tex->GetPosition() + Vector3(-speed, -speed, 0));
		}
	}
	else if (tex->GetRotation() == 315.0f)
	{
		if (animname == TexturePath + L"Bullet2.png")
		{
			tex->SetPosition(*tex->GetPosition() + Vector3(-speed, speed, 0));
		}
		else if (animname == TexturePath + L"Bullet.png")
		{
			tex->SetPosition(*tex->GetPosition() + Vector3(speed, -speed, 0));
		}
	}
	else if (tex->GetRotation() == 90.0f)
	{
		if (animname == TexturePath + L"Bullet.png")
		{
			tex->SetPosition(*tex->GetPosition() + Vector3(0, speed, 0));
		}
		else if (animname == TexturePath + L"Bullet2.png")
		{
			tex->SetPosition(*tex->GetPosition() - Vector3(0, speed, 0));
		}
	}
	else if (tex->GetRotation() == 270.0f)
	{
		if (animname == TexturePath + L"Bullet2.png")
		{
			tex->SetPosition(*tex->GetPosition() + Vector3(0, speed, 0));
		}
		else if (animname == TexturePath + L"Bullet.png")
		{
			tex->SetPosition(*tex->GetPosition() - Vector3(0, speed, 0));
		}
	}
	if (tex->GetPosition()->x < -90.0f||
	tex->GetPosition()->x > 1370.0f||
	tex->GetPosition()->y > 910.0f||
	tex->GetPosition()->y < -80.0f)
	{
		active = false;
	}
}

void Bullet::PotatoBulletUpdate()
{
	if (active == true)
	{
		tex->SetPosition(*tex->GetPosition() - Vector3(speed, 0, 0));
		hitbox->GetAnimRect()->SetPosition(*hitbox->GetAnimRect()->GetPosition() - Vector3(speed, 0, 0));
		if (tex->GetPosition()->x < -200.0f)
		{
			SetPotatoBulletPosition();
		}
	}
	
	
}



void Bullet::OnionBulletUpdate()
{
	if (active == true)
	{
		if (animator->GetEndAni(L"Onion_Bullet_Broken"))
		{
			active = false;
			SetOnionBulletPosition();
			animator->SetCurrentAnimClip(L"Onion_Bullet");
		}

		if (tex->GetPosition()->y > 140.0f && tex->GetAnimator()->GetClipName() != L"Onion_Bullet_Broken")
		{
			tex->SetPosition(*tex->GetPosition() - Vector3(0, speed, 0));
			hitbox->GetAnimRect()->SetPosition(*hitbox->GetAnimRect()->GetPosition() - Vector3(0, speed, 0));
		}
		else if (tex->GetPosition()->y <= 140.0f)
			animator->SetCurrentAnimClip(L"Onion_Bullet_Broken");
	}
}

void Bullet::CarrotBulletUpdate()
{
	if (animname == L"Carrot_Missile")
	{
		turnRotation = 270.0f + (float)D3DXToDegree(atan2(-height, -base));
		tex->SetRotation(turnRotation);
		hitbox->GetAnimRect()->SetRotation(turnRotation);
		nMovePoint = { base, height, 0 };
		D3DXVec3Normalize(&nMovePoint, &nMovePoint);
		tex->SetPosition(*(tex->GetPosition()) + (nMovePoint));
		hitbox->GetAnimRect()->SetPosition(*(hitbox->GetAnimRect()->GetPosition()) + nMovePoint);
		if(active==false)
			tex->SetPosition(Vector3( (float)(rand() % 1280), (float)(rand() % 780), 0 ));
	}

	if (hp < 0)
		SetCarrotBulletPosition();
}

void Bullet::CarrotBeamUpdate()
{
	if (lockOn)
	{
		base = targetPosition.x + 40.0f - tex->GetPosition()->x;
		height = targetPosition.y + 75.0f - tex->GetPosition()->y;
		nMovePoint = { base, height, 0 };
		D3DXVec3Normalize(&nMovePoint, &nMovePoint);
		lockOn = false;
	}

	if (animator->GetEndAni(L"Carrot_Beam_Ready"))
	{
		animator->SetCurrentAnimClip(L"Carrot_Beam");
	}

	tex->SetPosition((*(tex->GetPosition())) + (nMovePoint)*3.0f);
	hitbox->GetAnimRect()->SetPosition((*(hitbox->GetAnimRect()->GetPosition())) + (nMovePoint)*3.0f);

	if (tex->GetPosition()->y < 160)
	{
		tex->SetPosition(respawn);
		hitbox->GetAnimRect()->SetPosition(respawn);
		animator->SetCurrentAnimClip(L"Carrot_Beam_Ready");
		active = false;
	}
}

void Bullet::UpdateData()
{
	base = target->GetPosition().x + 40.0f - tex->GetPosition()->x ;
	height = target->GetPosition().y + 75.0f - tex->GetPosition()->y;
}
