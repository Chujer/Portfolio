#include "Framework.h"
#include "Player.h"
Player::Player(Vector3 position, Vector3 size)
	: Character(position, size)
{
	hitbox = new HitBox({ 260, 110, 0 }, { 80, 120, 1 }, "Player");
	Texture2D* srcTex1 = new Texture2D(TexturePath + L"/Player/playerAnimation.png");
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"/Player/Animation_L.png");
	Vector2 texSize = Vector2(srcTex1->GetWidth(), srcTex1->GetHeight());

	float scsizeX = texSize.x/28.0f;
	float scsizeY = texSize.y/25.0f;

	

	clips.push_back(new AnimationClip(L"IdleR", srcTex1, 9, Vector2(0, 0), Vector2(scsizeX * 9, scsizeY), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"IdleL", srcTex2, 10, Vector2(scsizeX * 6, 0), Vector2(scsizeX * 16, scsizeY), 1.0f / 22.0f,true));
	
	clips.push_back(new AnimationClip(L"Dash_R", srcTex1, 8, Vector2(0, scsizeY), Vector2(scsizeX * 8, scsizeY * 2), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Dash_L", srcTex2, 8, Vector2(scsizeX * 8, scsizeY), Vector2(scsizeX * 16, scsizeY * 2), 1.0f / 22.0f, true));
	
	clips.push_back(new AnimationClip(L"Jump_R", srcTex1, 8, Vector2(0, scsizeY * 2), Vector2(scsizeX * 8, scsizeY * 3), 1.0f / 32.0f));
	clips.push_back(new AnimationClip(L"Jump_L", srcTex2, 8, Vector2(scsizeX * 8, scsizeY * 2), Vector2(scsizeX * 16, scsizeY * 3), 1.0f / 32.0f, true));
	
	clips.push_back(new AnimationClip(L"Duck_Idle_R", srcTex1, 10, Vector2(0, scsizeY * 3), Vector2(scsizeX * 10, scsizeY * 4), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Duck_Idle_L", srcTex2, 10, Vector2(scsizeX * 6, scsizeY * 3), Vector2(scsizeX * 16, scsizeY * 4), 1.0f / 22.0f, true));
	clips.push_back(new AnimationClip(L"Duck_Shoot_R", srcTex1, 3, Vector2(0, scsizeY * 4), Vector2(scsizeX * 3, scsizeY * 5), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Duck_Shoot_L", srcTex2, 3, Vector2(scsizeX * 13, scsizeY * 4), Vector2(scsizeX * 16, scsizeY * 5), 1.0f / 22.0f, true));
	
	clips.push_back(new AnimationClip(L"On_Duck_R", srcTex1, 7, Vector2(0, scsizeY * 5), Vector2(scsizeX * 7, scsizeY * 6), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"On_Duck_L", srcTex2, 7, Vector2(scsizeX * 9, scsizeY * 5), Vector2(scsizeX * 16, scsizeY * 6), 1.0f / 22.0f, true));

	clips.push_back(new AnimationClip(L"RunN_R", srcTex1, 16, Vector2(0, scsizeY * 6), Vector2(scsizeX * 16, scsizeY * 7), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"RunN_L", srcTex2, 16, Vector2(0, scsizeY * 6), Vector2(scsizeX * 16, scsizeY * 7), 1.0f / 22.0f, true));
	clips.push_back(new AnimationClip(L"turn_RunN_R", srcTex1, 2, Vector2(0, scsizeY * 7), Vector2(scsizeX * 2, scsizeY * 8), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"turn_RunN_L", srcTex2, 2, Vector2(scsizeX * 14, scsizeY * 7), Vector2(scsizeX * 16, scsizeY * 8), 1.0f / 22.0f, true));

	clips.push_back(new AnimationClip(L"RunS_R", srcTex1, 16, Vector2(0, scsizeY * 8), Vector2(scsizeX * 16, scsizeY * 9), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"RunS_L", srcTex2, 16, Vector2(0, scsizeY * 8), Vector2(scsizeX * 16, scsizeY * 9), 1.0f / 22.0f, true));
	clips.push_back(new AnimationClip(L"turn_RunS_R", srcTex1, 2, Vector2(0, scsizeY * 9), Vector2(scsizeX * 2, scsizeY * 10), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"turn_RunS_L", srcTex2, 2, Vector2(scsizeX * 14, scsizeY * 9), Vector2(scsizeX * 16, scsizeY * 10), 1.0f / 22.0f, true));
	
	clips.push_back(new AnimationClip(L"RunS_UR", srcTex1, 16, Vector2(0, scsizeY * 10), Vector2(scsizeX * 16, scsizeY * 11), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"RunS_UL", srcTex2, 16, Vector2(0, scsizeY * 10), Vector2(scsizeX * 16, scsizeY * 11), 1.0f / 22.0f, true));
	clips.push_back(new AnimationClip(L"turn_RunS_UR", srcTex1, 2, Vector2(0, scsizeY * 11), Vector2(scsizeX * 2, scsizeY * 12), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"turn_RunS_UL", srcTex2, 2, Vector2(scsizeX * 14, scsizeY * 11), Vector2(scsizeX * 16, scsizeY * 12), 1.0f / 22.0f, true));

	clips.push_back(new AnimationClip(L"Shoot_DownR", srcTex1, 3, Vector2(0, scsizeY * 12), Vector2(scsizeX * 3, scsizeY * 13), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Shoot_DownL", srcTex2, 3, Vector2(scsizeX * 13, scsizeY * 12), Vector2(scsizeX * 16, scsizeY * 13), 1.0f / 22.0f, true));
	clips.push_back(new AnimationClip(L"Shoot_Straight_DownR", srcTex1, 3, Vector2(0, scsizeY * 13), Vector2(scsizeX * 3, scsizeY * 14), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Shoot_Straight_DownL", srcTex2, 3, Vector2(scsizeX * 13, scsizeY * 13), Vector2(scsizeX * 16, scsizeY * 14), 1.0f / 22.0f, true));
	clips.push_back(new AnimationClip(L"Shoot_StraightR", srcTex1, 3, Vector2(0, scsizeY * 14), Vector2(scsizeX * 3, scsizeY * 15), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Shoot_StraightL", srcTex2, 3, Vector2(scsizeX * 13, scsizeY * 14), Vector2(scsizeX * 16, scsizeY *15), 1.0f / 22.0f, true));
	clips.push_back(new AnimationClip(L"Shoot_Straight_UpR", srcTex1, 3, Vector2(0, scsizeY * 15), Vector2(scsizeX * 3, scsizeY * 16), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Shoot_Straight_UpL", srcTex2, 3, Vector2(scsizeX * 13, scsizeY * 15), Vector2(scsizeX * 16, scsizeY * 16), 1.0f / 22.0f, true));
	clips.push_back(new AnimationClip(L"Shoot_UpR", srcTex1, 3, Vector2(0, scsizeY * 16), Vector2(scsizeX * 3, scsizeY * 17), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Shoot_UpL", srcTex2, 3, Vector2(scsizeX * 13, scsizeY * 16), Vector2(scsizeX * 16, scsizeY * 17), 1.0f / 22.0f, true));


	clips.push_back(new AnimationClip(L"Aim_DownR", srcTex1, 10, Vector2(0, scsizeY * 17), Vector2(scsizeX * 10, scsizeY * 18), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_DownL", srcTex2, 10, Vector2(scsizeX * 6, scsizeY * 17), Vector2(scsizeX * 16, scsizeY * 18), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_Straight_DownR", srcTex1, 10, Vector2(0, scsizeY * 18), Vector2(scsizeX * 10, scsizeY * 19), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_Straight_DownL", srcTex2, 10, Vector2(scsizeX * 6, scsizeY * 18), Vector2(scsizeX * 16, scsizeY * 19), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_StraightR", srcTex1, 10, Vector2(0, scsizeY * 19), Vector2(scsizeX * 10, scsizeY * 20), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_StraightL", srcTex2, 10, Vector2(scsizeX * 6, scsizeY * 19), Vector2(scsizeX * 16, scsizeY * 20), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_Straight_UpR", srcTex1, 10, Vector2(0, scsizeY * 20), Vector2(scsizeX * 10, scsizeY * 21), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_Straight_UpL", srcTex2, 10, Vector2(scsizeX * 6, scsizeY * 20), Vector2(scsizeX * 16, scsizeY * 21), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_UpR", srcTex1, 10, Vector2(0, scsizeY * 21), Vector2(scsizeX * 10, scsizeY * 22), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Aim_UpL", srcTex2, 10, Vector2(scsizeX * 6, scsizeY * 21), Vector2(scsizeX * 16, scsizeY * 22), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Intro_R", srcTex1, 28, Vector2(0, scsizeY * 22), Vector2(scsizeX * 28.0f, scsizeY * 23), 1.0f / 22.0f));



	clips.push_back(new AnimationClip(L"Hit_R", srcTex1, 6, Vector2(0, scsizeY * 23), Vector2(scsizeX * 6.0f, scsizeY * 24), 1.0f / 22.0f));
	clips.push_back(new AnimationClip(L"Ghost_R", srcTex1, 24, Vector2(0, scsizeY * 24), Vector2(scsizeX * 24.0f, scsizeY * 25), 1.0f / 22.0f));


	animator->AddAnimClips(clips);

	animator->SetCurrentAnimClip(L"Intro_R");

	animRect->SetAnimation(animator);


	control = new Control(animRect->GetAnimator(), animRect->GetPosition());
}

Player::~Player()
{
	SAFE_DELETE(control);
}

void Player::Update()
{
	if (HP < 1)
	{
		is_Death = true;
	}
	
	if (animator->GetEndAni(L"Intro_R"))
		animator->SetCurrentAnimClip(L"IdleR");

	animator->Update();
	animRect->Update();
	hitbox->Update();


	if (is_Death == false)
	{
		if (animator->GetEndAni(L"Hit_R")|| animator->GetEndAni(L"Hit_L"))		//ÇÃ·¹ÀÌ¾î ¹«Àû½Ã°£ ¹Ø ±ôºýÀÓ
		{
			control->ChangeAnimation();
			hitAnimPoint = hitAnimPoint - 1;
		}
		if (hit == true)
		{
			if (hitAnimPoint == HP)
			{
				if (control->GetFacingLeft() == true)
					animator->SetCurrentAnimClip(L"Hit_L");
				else
					animator->SetCurrentAnimClip(L"Hit_R");
			}

			hitTime += Time::Delta();
			twinklingTime += Time::Delta();
			if (hitTime > hitSafeTime)
			{
				hit = false;
				point = 0;
				hitTime = 0.0f;
			}
		}
	}
	else
	{
		animRect->SetPosition(*animRect->GetPosition() + Vector3(0, 1.0f, 0));
	}
	

}

void Player::Render()
{
	if(is_Death==false)
		control->Update();
	if (twinklingTime > twinklingdelay)
	{
		if (point == 2)
		{
			point = 0;
			twinklingdelay = 0.3f;
		}
		else if (point == 0)
		{
			point = 2;
			twinklingdelay = 0.1f;
		}
		twinklingTime = 0.0f;
	}
	sb->SetPoint(point);
	sb->SetPSBuffer(0);


	animRect->Render();
	hitbox->Render();
}

void Player::Move()
{
	if (is_Death == false)
	{
		if (animator->GetClipName() != L"Intro_R")
		{
			if (control->GetPush_Left() == false)
			{
				control->Right(VK_RIGHT, 470, hitbox);
			}
			if (control->GetPush_Right() == false)
			{
				control->Left(VK_LEFT, 470, hitbox);
			}
			control->Up(VK_UP);
			control->Down(VK_DOWN);
			control->Aimming('C');
			if (control->GetDash() == false)
				control->Jump('Z', 900, hitbox);
			control->Attack('X');
			control->Dash(VK_LSHIFT, 900, hitbox);
			control->PlayerPositionYLock(hitbox);
		}
	}
	else if (is_Death == true)
	{
		control->Death();
	}
	//control->Skiil('A', 'S');
}

void Player::PlayerBulletOBB()
{
	control->OBB();
}

bool Player::GetActive()
{
	return false;
}

void Player::SetActive(bool active)
{
}
