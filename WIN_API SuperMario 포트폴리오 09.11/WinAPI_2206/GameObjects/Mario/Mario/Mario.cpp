#include "Framework.h"

Mario::Mario()
{
	Audio::Get()->Add("Jump", "Sounds/Jump.wav");
	Audio::Get()->Add("Attack", "Sounds/Fire Ball.wav");
	Audio::Get()->Add("Powerup", "Sounds/Powerup.wav");
	Audio::Get()->Add("Warp", "Sounds/Warp.wav");
	Audio::Get()->Add("Die", "Sounds/Die.wav");
	MarioEventManager::Get()->AddEvent("EatMushroom", bind(&Mario::EatMushroom, this));
	MarioEventManager::Get()->AddEvent("EatFlower", bind(&Mario::EatFlower, this));
	CreateAnimation();
	pos = { CENTER_X,CENTER_Y };
	SetSize();

	animations[curType]->Play();
	firstCamPos = Camera::Get()->GetPos();
}

Mario::~Mario()
{
	for (pair<ActionType, Animation*> animation : animations)
		delete animation.second;

	delete hitBox;
}

void Mario::Move()
{
	if (curType == CHANGE_MODE_L || curType == CHANGE_MODE_R)
	{
		velocity.x = 0;
		return;
	}
	speed = 500.0f;
	if (KEY_PRESS(VK_SHIFT))
	{
		speed = 1000.0f;

		animations[RUN_R]->SetFrameUpdateTime(0.05f);
		animations[RUN_L]->SetFrameUpdateTime(0.05f);
	}
	else if(KEY_UP(VK_SHIFT))
	{
		animations[RUN_R]->SetFrameUpdateTime(0.1f);
		animations[RUN_L]->SetFrameUpdateTime(0.1f);
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		velocity.x += speed * DELTA;

		if (curType == RUN_L)
			SetAction(BRAKE_R);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		velocity.x -= speed * DELTA;
		if (curType == RUN_R)
			SetAction(BRAKE_L);
	}


	velocity.x = Clamp(-MAX_VELOCITY, MAX_VELOCITY, velocity.x);

	velocity.x = LERP(velocity.x, 0.0f, DECEL * DELTA);


	if (velocity.x > 0.0f)
		isRight = true;
	else if (velocity.x < 0.0f)
		isRight = false;

}

void Mario::Jump()
{
	if (jumpCount < MAX_JUMP_COUNT && KEY_DOWN('Z'))
	{
		Audio::Get()->Play("Jump",0.7f);
		velocity.y = -JUMP_POWER;
		jumpCount++;
	}

	velocity.y += GRAVITY * DELTA;

}

void Mario::Shooting()
{
	if (mode != FLOWER) return;

	if (KEY_DOWN('X'))
	{
		BulletManager::Get()->CreateBullet(pos, isRight);
		Audio::Get()->Play("Attack",0.7f);
		if(isRight)
			SetAction(ATTACK_R);
		else
			SetAction(ATTACK_L);
	}
}

void Mario::Die()
{
	if (jumpCount < 2)
	{
		velocity.y = -JUMP_POWER*0.7f;
	}
	jumpCount++;

	velocity.y += GRAVITY * DELTA;
	velocity.x = 0;
}

void Mario::Update()
{
	//ImageRect::Update();
	animations[curType]->Update();

	if (mode == CHANGE_MODE || mode == CHANGE_FLOWER_MODE) return;

	if (!isDie)
	{
		SetAnimation();
		Move();
		Jump();
		Shooting();
	}
	else
	{
		Die();
	}

	pos += velocity * DELTA;

	if (isDie == true)
		SetAction(DIE);
	if (KEY_DOWN(VK_SPACE))
		EatFlower();

	if (pos.y > WIN_HEIGHT)
	{
		if (!isDie)
			MarioGameManager::Get()->PlayerLife()--;

		MarioGameManager::Get()->ChangeScene("UIScene");
	}
}

void Mario::Render(HDC hdc)
{
	ImageRect::CamRender(hdc,animations[curType]->GetFrame());
}

void Mario::IsHit()
{
	if (mode == CHANGE_MODE || mode == CHANGE_FLOWER_MODE) return;
	beforeMode = mode;
	switch (mode)
	{
	case Mario::SMALL:
		//velocity.y = -JUMP_POWER / 20;
		isDie = true;
		MarioGameManager::Get()->PlayerLife()--;
		Audio::Get()->Play("Die", 0.6f);
		Audio::Get()->Stop("stage1BGM");
		Audio::Get()->Stop("stage2BGM");
		//MessageBox(hWnd, L"GameOver", L"GameOver", MB_OK);
		break;
	case Mario::BIG:
		Audio::Get()->Play("Warp", 0.7f);
		mode = CHANGE_MODE;
		SetTexture(changeMarioMushroomAnimation);
		if (isRight)
		{
			SetAction(CHANGE_MODE_R);
		}
		else
		{
			SetAction(CHANGE_MODE_L);
		}
		SetSize();
		break;
	case Mario::FLOWER:
		mode = CHANGE_FLOWER_MODE;
		Audio::Get()->Play("Warp", 0.7f);
		
		SetTexture(changeMarioFlowerAnimation);
		if (isRight)
		{
			SetAction(FLOWER_CHANGE_MODE_R);
		}
		else
		{
			SetAction(FLOWER_CHANGE_MODE_L);
		}
		SetSize();
		break;
	default:
		break;
	}
}

void Mario::PushEnemy()
{
	velocity.y = -JUMP_POWER/2;
}

void Mario::EatMushroom()
{
	MarioGameManager::Get()->Score() += 1000;
	if (mode != SMALL) 
		return;

	beforeMode = mode;
	mode = CHANGE_MODE;
	Audio::Get()->Play("Powerup", 0.7f);
	SetTexture(changeMarioMushroomAnimation);
	if (isRight)
	{
		SetAction(CHANGE_MODE_R);
	}
	else
	{
		SetAction(CHANGE_MODE_L);
	}
	SetSize();
}

void Mario::EatFlower()
{
	MarioGameManager::Get()->Score() += 1000;
	if (mode == FLOWER)
		return;

	beforeMode = mode;

	if (mode == SMALL)
		beforeMode = BIG;

	mode = CHANGE_MODE;
	Audio::Get()->Play("Powerup",0.7f);
	SetTexture(changeMarioFlowerAnimation);
	if (isRight)
	{
		SetAction(FLOWER_CHANGE_MODE_R);
	}
	else
	{
		SetAction(FLOWER_CHANGE_MODE_L);
	}
	SetSize();
}

void Mario::EndChangeMushroomAnimation()		// 함수포인터로 호출
{
	if (beforeMode == SMALL)
	{
		mode = BIG;
		ChangeSmallToBig();
		if (isRight)
			SetAction(IDLE_R);
		else
			SetAction(IDLE_L);
	}
	else if (beforeMode == BIG)
	{
		mode = SMALL;
		ChangeBigToSmall();
		if (isRight)
			SetAction(IDLE_R);
		else
			SetAction(IDLE_L);
	}
	SetSize();
	velocity = { 0,0 };
}

void Mario::EndChangeFlowerAnimation()
{
	if (beforeMode == BIG || beforeMode == SMALL)
	{
		mode = FLOWER;
		ChangeFlower();
		if (isRight)
			SetAction(IDLE_R);
		else
			SetAction(IDLE_L);
	}
	else if (beforeMode == FLOWER)
	{
		mode = BIG;
		ChangeSmallToBig();
		if (isRight)
			SetAction(IDLE_R);
		else
			SetAction(IDLE_L);
	}
	SetSize();
	velocity = { 0,0 };
}

void Mario::IsOnTheGround(Vector2 Ground)
{
	//pos.y = Ground.y - Half().y;
	if (isDie) return;

	if (jumpCount == 0)
		velocity.y = 0;

	jumpCount = 0;
}

void Mario::SetAnimation()
{
	if (curType==CHANGE_MODE_L||curType==CHANGE_MODE_R) return;

	if(velocity.y != 0)
	{
		if (isRight)
			SetAction(JUMP_R);
		else
			SetAction(JUMP_L);

		return;
	}
	if (velocity.x > 50.0f)
		SetAction(RUN_R);
	else if (velocity.x < -50.0f)
		SetAction(RUN_L);
	else if (!isRight)
		SetAction(IDLE_L);
	else if (isRight)
		SetAction(IDLE_R);

}

void Mario::CreateAnimation()
{
	smallMarioAnimation = TEXTURE->Add(L"Textures/newMario/SmallMario.bmp", 72, 108, 4, 6, MAGENTA);
	bigMarioAnimation = TEXTURE->Add(L"Textures/newMario/BigMario.bmp", 64, 192, 4, 6, MAGENTA);
	changeMarioMushroomAnimation = TEXTURE->Add(L"Textures/newMario/ChangeModeMushroom.bmp", 216, 68, 12, 2, MAGENTA);
	changeMarioFlowerAnimation = TEXTURE->Add(L"Textures/newMario/ChangeModeFlower.bmp", 128, 64, 8, 2, MAGENTA);
	FlowerMarioAnimation = TEXTURE->Add(L"Textures/newMario/FlowerMario.bmp", 64, 192, 4, 6, MAGENTA);

	SetTexture(smallMarioAnimation);

	animations[IDLE_R] = new Animation(smallMarioAnimation->GetFrame());
	animations[IDLE_R]->SetPart(0, 0, true);

	animations[IDLE_L] = new Animation(smallMarioAnimation->GetFrame());
	animations[IDLE_L]->SetReversePart(15, 15, true);

	animations[JUMP_R] = new Animation(smallMarioAnimation->GetFrame());
	animations[JUMP_R]->SetPart(4, 4, true);

	animations[JUMP_L] = new Animation(smallMarioAnimation->GetFrame());
	animations[JUMP_L]->SetReversePart(19, 19, true);

	animations[RUN_R] = new Animation(smallMarioAnimation->GetFrame());
	animations[RUN_R]->SetPart(9, 11, true);

	animations[RUN_L] = new Animation(smallMarioAnimation->GetFrame());
	animations[RUN_L]->SetReversePart(20, 22, true);

	animations[BRAKE_R] = new Animation(smallMarioAnimation->GetFrame());
	animations[BRAKE_R]->SetPart(8, 8, true);

	animations[BRAKE_L] = new Animation(smallMarioAnimation->GetFrame());
	animations[BRAKE_L]->SetPart(23, 23, true);

	animations[CHANGE_MODE_R] = new Animation(changeMarioMushroomAnimation->GetFrame());
	animations[CHANGE_MODE_R]->SetPart(0, 11);
	animations[CHANGE_MODE_R]->SetEndEvent(bind(&Mario::EndChangeMushroomAnimation, this));

	animations[CHANGE_MODE_L] = new Animation(changeMarioMushroomAnimation->GetFrame());
	animations[CHANGE_MODE_L]->SetReversePart(12, 23);
	animations[CHANGE_MODE_L]->SetEndEvent(bind(&Mario::EndChangeMushroomAnimation, this));

	animations[FLOWER_CHANGE_MODE_R] = new Animation(changeMarioFlowerAnimation->GetFrame());
	animations[FLOWER_CHANGE_MODE_R]->SetPart(0, 8);
	animations[FLOWER_CHANGE_MODE_R]->SetEndEvent(bind(&Mario::EndChangeFlowerAnimation, this));

	animations[FLOWER_CHANGE_MODE_L] = new Animation(changeMarioFlowerAnimation->GetFrame());
	animations[FLOWER_CHANGE_MODE_L]->SetReversePart(9, 15);
	animations[FLOWER_CHANGE_MODE_L]->SetEndEvent(bind(&Mario::EndChangeFlowerAnimation, this));

	animations[DIE] = new Animation(smallMarioAnimation->GetFrame());
	animations[DIE]->SetPart(1, 1, true);
}

void Mario::SetAction(ActionType type)
{
	if (curType == type) return;

	curType = type;
	animations[type]->Play();

}

void Mario::ChangeSmallToBig()
{
	SetTexture(bigMarioAnimation);
	size = texture->GetSize() * 3.0f;

	animations[IDLE_R] = new Animation(bigMarioAnimation->GetFrame());
	animations[IDLE_R]->SetPart(0, 0, true);

	animations[IDLE_L] = new Animation(bigMarioAnimation->GetFrame());
	animations[IDLE_L]->SetReversePart(15, 15, true);

	animations[SIT_R] = new Animation(bigMarioAnimation->GetFrame());
	animations[SIT_R]->SetPart(1, 1, true);

	animations[SIT_L] = new Animation(bigMarioAnimation->GetFrame());
	animations[SIT_L]->SetPart(14, 14, true);

	animations[JUMP_R] = new Animation(bigMarioAnimation->GetFrame());
	animations[JUMP_R]->SetPart(4, 4, true);

	animations[JUMP_L] = new Animation(bigMarioAnimation->GetFrame());
	animations[JUMP_L]->SetReversePart(19, 19, true);

	animations[RUN_R] = new Animation(bigMarioAnimation->GetFrame());
	animations[RUN_R]->SetPart(9, 11, true);

	animations[RUN_L] = new Animation(bigMarioAnimation->GetFrame());
	animations[RUN_L]->SetReversePart(20, 22, true);

	animations[BRAKE_R] = new Animation(bigMarioAnimation->GetFrame());
	animations[BRAKE_R]->SetPart(8, 8, true);

	animations[BRAKE_L] = new Animation(bigMarioAnimation->GetFrame());
	animations[BRAKE_L]->SetPart(23, 23, true);


}

void Mario::ChangeBigToSmall()
{
	SetTexture(smallMarioAnimation);
	size = texture->GetSize() * 3.0f;

	animations[IDLE_R] = new Animation(smallMarioAnimation->GetFrame());
	animations[IDLE_R]->SetPart(0, 0, true);

	animations[IDLE_L] = new Animation(smallMarioAnimation->GetFrame());
	animations[IDLE_L]->SetReversePart(15, 15, true);

	animations[JUMP_R] = new Animation(smallMarioAnimation->GetFrame());
	animations[JUMP_R]->SetPart(4, 4, true);

	animations[JUMP_L] = new Animation(smallMarioAnimation->GetFrame());
	animations[JUMP_L]->SetReversePart(19, 19, true);

	animations[RUN_R] = new Animation(smallMarioAnimation->GetFrame());
	animations[RUN_R]->SetPart(9, 11, true);

	animations[RUN_L] = new Animation(smallMarioAnimation->GetFrame());
	animations[RUN_L]->SetReversePart(20, 22, true);

	animations[BRAKE_R] = new Animation(smallMarioAnimation->GetFrame());
	animations[BRAKE_R]->SetPart(8, 8, true);

	animations[BRAKE_L] = new Animation(smallMarioAnimation->GetFrame());
	animations[BRAKE_L]->SetPart(23, 23, true);

}

void Mario::ChangeFlower()
{
	SetTexture(FlowerMarioAnimation);
	size = texture->GetSize() * 3.0f;

	animations[IDLE_R] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[IDLE_R]->SetPart(0, 0, true);

	animations[IDLE_L] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[IDLE_L]->SetReversePart(15, 15, true);

	animations[SIT_R] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[SIT_R]->SetPart(1, 1, true);

	animations[SIT_L] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[SIT_L]->SetPart(14, 14, true);

	animations[JUMP_R] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[JUMP_R]->SetPart(4, 4, true);

	animations[JUMP_L] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[JUMP_L]->SetReversePart(19, 19, true);

	animations[RUN_R] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[RUN_R]->SetPart(9, 11, true);

	animations[RUN_L] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[RUN_L]->SetReversePart(20, 22, true);

	animations[BRAKE_R] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[BRAKE_R]->SetPart(8, 8, true);

	animations[BRAKE_L] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[BRAKE_L]->SetPart(23, 23, true);

	animations[ATTACK_R] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[ATTACK_R]->SetPart(5, 5, true);

	animations[ATTACK_L] = new Animation(FlowerMarioAnimation->GetFrame());
	animations[ATTACK_L]->SetPart(18, 18, true);
}
