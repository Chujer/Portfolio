#include "Framework.h"
#include "Control.h"

Control::Control(Animator* animator, Vector3* position)
	:animator(animator), position(position)
{
	shootSpeed = 10.0f;
	srand(time(NULL));
	bulletPosition = new BulletPosition();
	shootEffect = new Effect(bulletPosition->GetShootPosition(*position, "rightX", "centerY"),Vector3(100,100,1),L"player_Bullet_Effect");
	shootEffect->ChangeEffect(*position, Vector3(100, 100, 1), true);
	for (int i = 0; i < 30; i++)
	{
		bullet[i] = new Bullet(bulletPosition->GetShootPosition(*position, "jumpX", "jumpY"), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png", 270.0f);
		bullet[i]->SetActive(false);
	}
}

Control::~Control()
{
	SAFE_DELETE(shootEffect);
	SAFE_DELETE(animator);
	SAFE_DELETE(potato);
	SAFE_DELETE(onion);
	SAFE_DELETE(carrot);
	for (int i = 0; i < 30; i++)
	{
		SAFE_DELETE(bullet[i]);
	}
}

void Control::Update()
{
	if (shootEffectActive == true && is_Dash==false)
	{
		ChangeEffectPosition();

		shootEffect->Update();
		shootEffect->Render();
	}
	for (Bullet* b : bullet)			
	{
		b->Update();
	}
}

void Control::Right(DWORD key, float speed, HitBox* hitbox)
{
	if (Keyboard::Get()->Press(key))
	{
		is_FacingLeft = false;
		if(is_Dash==false)
			is_PushRight = true;
		if (is_Aiming == false && is_PushDown == false && (*position).x < 1050.0f)
		{
			is_Move = true;
			if (is_Dash == false)
			{
				(*position).x += (speed * Time::Delta());
				//cout << hitbox->GetAnimRect()->GetPosition()->x;
				hitbox->MoveHitBox(Vector3((speed * Time::Delta()), 0, 0));
				shootEffect->GetAnimRect()->SetPosition(*shootEffect->GetAnimRect()->GetPosition()+(speed*Time::Delta(),0,0));
			}
		}
		ChangeAnimation();
	}
	else if (Keyboard::Get()->Up(key))
	{
		is_PushRight = false;
		is_Move = false;
		ChangeAnimation();
	}
}

void Control::Left(DWORD key, float speed, HitBox* hitbox)
{
	if (Keyboard::Get()->Press(key))
	{
		is_FacingLeft = true;
		if(is_Dash==false)
			is_PushLeft = true;
		if (is_Aiming == false && is_PushDown == false && (*position).x>-180.0f)
		{
			is_Move = true;
			if (is_Dash == false)
			{
				position->x -= (speed * Time::Delta());
				hitbox->MoveHitBox(Vector3((speed * Time::Delta()) * -1.0f, 0, 0));
			}
		}
		ChangeAnimation();
	}
	else if (Keyboard::Get()->Up(key))
	{
		is_Move = false;
		is_PushLeft = false;
		ChangeAnimation();
	}
}

void Control::Aimming(DWORD key)
{
	if (Keyboard::Get()->Press(key))
	{
		ChangeAnimation();
		is_Aiming = true;
	}
	else if (Keyboard::Get()->Up(key))
	{
		is_Aiming = false;
		ChangeAnimation();
	}
}

void Control::Up(DWORD key)
{
	if (Keyboard::Get()->Down(key))
	{
		is_PushUp = true;
		ChangeAnimation();
	}
	if (Keyboard::Get()->Press(key))
	{
		//is_Aiming = true;
		is_PushUp = true;
	}
	else if (Keyboard::Get()->Up(key))
	{
		//is_Aiming = false;
		is_PushUp = false;
		ChangeAnimation();
	}
}

void Control::Down(DWORD key)
{
	if (Keyboard::Get()->Down(key))
	{
		is_PushLeft = false;
		is_PushRight = false;
		is_Move = false;
		ChangeAnimation();
	}
	if (Keyboard::Get()->Press(key))
	{
		is_Duck = true;
		is_PushDown = true;
		ChangeAnimation();
	}
	else if (Keyboard::Get()->Up(key))
	{
		is_Duck = false;
		is_PushDown = false;
		ChangeAnimation();
	}
}

void Control::Jump(DWORD key, float speed, HitBox* hitbox)
{
	deltaTime += Time::Delta();

	if (is_Jump == false)
	{
		if (Keyboard::Get()->Down(key))
		{
			keyDown = 0.0f;
			is_PushDown = true;
		}
		if(is_PushDown == true)
		{
			if (Keyboard::Get()->Press(key))
			{
				keyDown += Time::Delta();
				if (keyDown > 0.07f)
				{
					is_Jump = true;
					deltaTime = 0.0f;
					jumpPower = 1.0f;
					is_PushDown = false;
				}
			}
			if (Keyboard::Get()->Up(key))
			{
				if (is_Jump == false)
				{
					is_Jump = true;
					deltaTime = 0.0f;
					jumpPower = 0.8f;
				}
				is_PushDown = false;
			}
		}
	}
	if (is_Jump == true)
	{
		if (jumpPower == 1.0f)
		{
			if ((deltaTime) < jumpTime)
				ChangeAnimation();		//�ִϸ��̼� ����

			if (deltaTime < (jumpTime / 2) - jumpStopTime - Time::Delta())
			{
				position->y += jumpPower * speed * Time::Delta();
				hitbox->MoveHitBox(Vector3(0, jumpPower * speed * Time::Delta(), 0));
			}
			else if (deltaTime < (jumpTime / 2))
			{
				position->y += 40 * Time::Delta();
				hitbox->MoveHitBox(Vector3(0, (40 * Time::Delta()), 0));
			}
			else if (deltaTime < (jumpTime / 2) + jumpStopTime)
			{
				position->y -= 40 * Time::Delta();
				hitbox->MoveHitBox(Vector3(0, (40 * Time::Delta())* -1.0f, 0));
			}
			else if (deltaTime < jumpTime)
			{
				position->y -= jumpPower * speed * Time::Delta();
				hitbox->MoveHitBox(Vector3(0, (jumpPower * speed) * -1.0f * Time::Delta(), 0));
			}
			else if (deltaTime > jumpTime)
			{
				is_Jump = false;
				ChangeAnimation();
			}
		}
		else if (jumpPower != 1.0f)
		{
			if ((deltaTime) < shallowJumpTime)
				ChangeAnimation();		//�ִϸ��̼� ����

			if (deltaTime < (shallowJumpTime / 2) - shallowJumpStopTime)
			{
				position->y += jumpPower * speed * Time::Delta();
				hitbox->MoveHitBox(Vector3(0, jumpPower * speed * Time::Delta(), 0));
			}
			else if (deltaTime < (shallowJumpTime / 2))
			{
				position->y += 40 * Time::Delta();
				hitbox->MoveHitBox(Vector3(0, (40 * Time::Delta()), 0));
			}
			else if (deltaTime < (shallowJumpTime / 2) + shallowJumpStopTime)
			{
				position->y -= 40 * Time::Delta();
				hitbox->MoveHitBox(Vector3(0, (40 * Time::Delta())*-1.0f, 0));
			}
			else if (deltaTime < shallowJumpTime)
			{
				position->y -= jumpPower * speed * Time::Delta();
				hitbox->MoveHitBox(Vector3(0, (jumpPower * speed * Time::Delta()) * -1.0f, 0));
			}
			else if (deltaTime > shallowJumpTime)
			{
				is_Jump = false;
				ChangeAnimation();

			}
		}
	}
}

void Control::PlayerPositionYLock(HitBox *hitbox)
{
	if (is_Jump == false)
	{
		position->y = LockPlayerPositionY;
		hitbox->GetAnimRect()->SetPosition(Vector3(hitbox->GetAnimRect()->GetPosition()->x, LockHitboxPositionY, 0));
	}
}

void Control::ChangeEffectPosition()
{
	if (is_Jump == true)
	{
		if (is_PushUp == true)
		{
			if (is_FacingLeft == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "jumpX", "jumpY"));
			}
			else if (is_FacingLeft == false)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "jumpX", "jumpY"));
			}
		}
		else
		{
			if (is_FacingLeft == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "leftX", "centerY"));
			}
			else if (is_FacingLeft == false)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "rightX", "centerY"));
			}
		}
	}
	else if (is_Aiming == true)
	{
		if (is_PushDown == true)
		{
			if (is_PushLeft == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "leftX", "diagonalDownY"));
			}
			else if (is_PushRight == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "rightX", "diagonalDownY"));
			}
			else if (is_FacingLeft == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "DownLeftX", "downY"));
			}
			else if (is_FacingLeft == false)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "DownRightX", "downY"));
			}
		}
		else if (is_PushUp == true)
		{
			if (is_PushLeft == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "leftX", "diagonalUpY"));
			}
			else if (is_PushRight == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "rightX", "diagonalUpY"));
			}
			else if (is_FacingLeft == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "upLeftX", "upY"));
			}
			else if (is_FacingLeft == false)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "upRightX", "upY"));
			}
		}
		else
		{
			if (is_FacingLeft == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "leftX", "centerY"));
			}
			else if (is_FacingLeft == false)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "rightX", "centerY"));
			}
		}
	}
	else
	{
		if (is_Duck == true)
		{
			if (is_FacingLeft == true)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "leftX", "duckY"));
			}
			else if (is_FacingLeft == false)
			{
				shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "rightX", "duckY"));
			}
		}
		else if (is_Move == true)
		{
			if (is_PushUp == true)
			{
				if (is_PushLeft == true)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "leftX", "diagonalUpY"));
				}
				else if (is_PushRight == true)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "rightX", "diagonalUpY"));
				}
				else if (is_FacingLeft == true)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "upLeftX", "upY"));
				}
				else if (is_FacingLeft == false)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "upRightX", "upY"));
				}
			}
			else
			{
				if (is_PushLeft == true)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "leftX", "moveShootY"));
				}
				else if (is_PushRight == true)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "rightX", "moveShootY"));
				}
			}
		}
		else
		{
			if (is_PushUp == true)
			{
				if (is_FacingLeft == true)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "upLeftX", "upY"));
				}
				else if (is_FacingLeft == false)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "upRightX", "upY"));
				}
			}
			else
			{
				if (is_FacingLeft == true)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "leftX", "centerY"));
				}
				else if (is_FacingLeft == false)
				{
					shootEffect->GetAnimRect()->SetPosition(bulletPosition->GetShootPosition(*position, "rightX", "centerY"));
				}
			}
		}
	}
}

void Control::Dash(DWORD key, float pos, HitBox * hitbox)
{
	dashDeltTime += Time::Delta();
	if (Keyboard::Get()->Down(VK_LSHIFT))
	{
		if (is_Dash == false)
		{
			dashDeltTime = 0.0f;
			is_Dash = true;
		}
	}
	if (is_Dash == true)
	{
		if (dashDeltTime < dashTime)
		{
			if (is_FacingLeft == true)
			{
				ChangeAnimation();
				position->x -= pos * Time::Delta();
				hitbox->MoveHitBox(Vector3(-pos * Time::Delta(), 0, 0));
			}
			else if(is_FacingLeft == false)
			{
				ChangeAnimation();
				position->x += pos * Time::Delta();
				hitbox->MoveHitBox(Vector3(pos * Time::Delta(), 0, 0));
			}
		}
		else if (dashDeltTime > dashTime)
		{
			is_Dash = false;
			ChangeAnimation();
			if (is_Jump == true)
			{
				printf("JumpPower : %f \n", jumpPower);
				if (jumpPower == 1)
				{
					if (deltaTime < jumpTime/2)
					{
						printf("FULL\n");
						deltaTime += (jumpTime /2.0f - deltaTime )*2.0f - Time::Delta()*1.4f;
					}
				}
				else if(jumpPower != 1)
				{
					printf("SHOT\n");
					if (deltaTime < shallowJumpTime / 2)
						deltaTime += (shallowJumpTime / 2.0f - deltaTime)*2.0f;
				}
			}
			dashDeltTime = 0.0f;
		}
	}
}

void Control::Death()
{
	animator->SetCurrentAnimClip(L"Ghost_R");
}


void Control::ChangeAnimation()
{
	//animator->GetClipName();
	animWaitTime += Time::Delta();
	if (is_Dash == false)
	{
		if (is_Aiming == true)		//Ű�Էº� ����(C)������ �ִϸ��̼�
		{
			if (is_Jump == false)		//���� ����
			{
				if (is_Attack == true)	//C+X �� ������ ���� �ִϸ��̼�	
				{
					if (is_PushDown == true)
					{
						if (is_PushLeft == true)
							animator->SetCurrentAnimClip(L"Shoot_Straight_DownL");
						else if (is_PushRight == true)
							animator->SetCurrentAnimClip(L"Shoot_Straight_DownR");
						else if (is_PushLeft == false && is_PushRight == false)
						{
							if (is_FacingLeft == true)
								animator->SetCurrentAnimClip(L"Shoot_DownL");
							else if (is_FacingLeft == false)
								animator->SetCurrentAnimClip(L"Shoot_DownR");
						}
					}
					else if (is_PushUp == true)
					{
						if (is_PushLeft == true)
							animator->SetCurrentAnimClip(L"Shoot_Straight_UpL");
						else if (is_PushRight == true)
							animator->SetCurrentAnimClip(L"Shoot_Straight_UpR");
						else if (is_PushLeft == false && is_PushRight == false)
						{
							if (is_FacingLeft == true)
								animator->SetCurrentAnimClip(L"Shoot_UpL");
							else if (is_FacingLeft == false)
								animator->SetCurrentAnimClip(L"Shoot_UpR");
						}
					}
					else if (is_FacingLeft == true)
					{
						animator->SetCurrentAnimClip(L"Shoot_StraightL");
					}
					else if (is_FacingLeft == false)
					{
						animator->SetCurrentAnimClip(L"Shoot_StraightR");
					}
				}
				else if (is_Attack == false)		//X�� ���������� ���ؾִϸ��̼�
				{
					if (is_PushDown == true)
					{
						if (is_PushLeft == true)
							animator->SetCurrentAnimClip(L"Aim_Straight_DownL");
						else if (is_PushRight == true)
							animator->SetCurrentAnimClip(L"Aim_Straight_DownR");
						else if (is_PushLeft == false && is_PushRight == false)
						{
							if (is_FacingLeft == true)
								animator->SetCurrentAnimClip(L"Aim_DownL");
							else if (is_FacingLeft == false)
								animator->SetCurrentAnimClip(L"Aim_DownR");
						}
					}
					else if (is_PushUp == true)
					{
						if (is_PushLeft == true)
							animator->SetCurrentAnimClip(L"Aim_Straight_UpL");
						else if (is_PushRight == true)
							animator->SetCurrentAnimClip(L"Aim_Straight_UpR");
						else if (is_PushLeft == false && is_PushRight == false)
						{
							if (is_FacingLeft == true)
								animator->SetCurrentAnimClip(L"Aim_UpL");
							else if (is_FacingLeft == false)
								animator->SetCurrentAnimClip(L"Aim_UpR");
						}
					}
					else if (is_FacingLeft == true)
					{
						animator->SetCurrentAnimClip(L"Aim_StraightL");
					}
					else if (is_FacingLeft == false)
					{
						animator->SetCurrentAnimClip(L"Aim_StraightR");
					}
				}
			}
			else if (is_Jump == true)		//������ �����ִϸ��̼� ���� ���
			{
				if (is_FacingLeft == true)
				{
					animator->SetCurrentAnimClip(L"Jump_L");
				}
				else if (is_FacingLeft == false)
				{
					animator->SetCurrentAnimClip(L"Jump_R");
				}
			}
		}
		else if (is_Aiming == false)	//C�� ���������� ���� ����
		{
			if (is_Jump == true)
			{
				if (is_FacingLeft == true)
				{
					animator->SetCurrentAnimClip(L"Jump_L");
				}
				else if (is_FacingLeft == false)
				{
					animator->SetCurrentAnimClip(L"Jump_R");
				}
			}
			else if (is_Jump == false)
			{
				if (is_Move == true)	//ĳ���� �̵��� �ִϸ��̼�
				{
					if (is_Duck == false)
					{
						if (is_Attack == true)		//�̵��� ����
						{
							if (is_FacingLeft == true)
							{
								if (is_PushUp == true)
								{
									if (animator->GetClipName() == L"Shoot_UpR")
									{
										animWaitTime = 0.0f;
										animator->SetCurrentAnimClip(L"turn_RunS_UL");
									}
									else if (animWaitTime > 0.1f)
										animator->SetCurrentAnimClip(L"RunS_UL");
								}
								else if (is_PushUp == false)
								{
									if (animator->GetClipName() == L"Shoot_StraightR")
									{
										animWaitTime = 0.0f;
										animator->SetCurrentAnimClip(L"turn_RunS_L");
									}
									else if (animWaitTime > 0.1f)
										animator->SetCurrentAnimClip(L"RunS_L");
								}
							}
							else if (is_FacingLeft == false)
							{
								if (is_PushUp == true)
								{
									if (animator->GetClipName() == L"Shoot_UpL")
									{
										animWaitTime = 0.0f;
										animator->SetCurrentAnimClip(L"turn_RunS_UR");
									}
									else if (animWaitTime > 0.1f)
										animator->SetCurrentAnimClip(L"RunS_UR");
								}
								else if (is_PushUp == false)
								{
									if (animator->GetClipName() == L"Shoot_StraightL")
									{
										animWaitTime = 0.0f;
										animator->SetCurrentAnimClip(L"turn_RunS_R");
									}
									else if (animWaitTime > 0.1f)
										animator->SetCurrentAnimClip(L"RunS_R");
								}
							}
						}
						else if (is_Attack == false)		//�Ϲ� �̵�
						{
							if (is_FacingLeft == true)
							{
								if (animator->GetClipName() == L"IdleR")
								{
									animWaitTime = 0.0f;
									animator->SetCurrentAnimClip(L"turn_RunN_L");
								}
								else if (animWaitTime > 0.1f)
									animator->SetCurrentAnimClip(L"RunN_L");
							}
							else
							{
								if (animator->GetClipName() == L"IdleL")
								{
									animWaitTime = 0.0f;
									animator->SetCurrentAnimClip(L"turn_RunN_R");
								}
								else if (animWaitTime > 0.1f)
									animator->SetCurrentAnimClip(L"RunN_R");
							}
						}
					}
					else if (is_Duck == true)
					{
						if (is_Attack == true)
						{
							if (is_FacingLeft == true)
							{
								animator->SetCurrentAnimClip(L"Duck_Shoot_L");
							}
							else
							{
								animator->SetCurrentAnimClip(L"Duck_Shoot_R");
							}
						}
						else if (is_Attack == false)
						{
							if (is_FacingLeft == true)
							{
								animator->SetCurrentAnimClip(L"Duck_Idle_L");
							}
							else
							{
								animator->SetCurrentAnimClip(L"Duck_Idle_R");
							}
						}
					}
				}
				else if (is_Move == false)		//�̵����� ������
				{
					if (is_Duck == true)		//�Ʒ�Ű �Է½� �ִϸ��̼�
					{
						if (is_Attack == true)
						{
							if (is_FacingLeft == true)
							{
								animator->SetCurrentAnimClip(L"Duck_Shoot_L");
							}
							else
							{
								animator->SetCurrentAnimClip(L"Duck_Shoot_R");
							}
						}
						else if (is_Attack == false)
						{
							if (is_FacingLeft == true)
							{
								if (animator->GetClipName() == L"IdleL")
								{
									animWaitTime = 0.0f;
									animator->SetCurrentAnimClip(L"On_Duck_L");
								}
								else if (animWaitTime > 0.1f)
									animator->SetCurrentAnimClip(L"Duck_Idle_L");
							}
							else
							{
								if (animator->GetClipName() == L"IdleR")
								{
									animWaitTime = 0.0f;
									animator->SetCurrentAnimClip(L"On_Duck_R");
								}
								else if (animWaitTime > 0.1f)
									animator->SetCurrentAnimClip(L"Duck_Idle_R");
							}
						}
					}
					else if (is_Duck == false)		//�Ϲ� ����
					{
						if (is_Attack == true)		//���ڸ����� ����(X)Ű���� ������
						{

							if (is_FacingLeft == true)
							{
								if (is_PushUp == true)
								{
									animator->SetCurrentAnimClip(L"Shoot_UpL");
								}
								else if (is_PushUp == false)
								{
									animator->SetCurrentAnimClip(L"Shoot_StraightL");
								}
							}
							else
							{
								if (is_PushUp == true)
								{
									animator->SetCurrentAnimClip(L"Shoot_UpR");
								}
								else if (is_PushUp == false)
								{
									animator->SetCurrentAnimClip(L"Shoot_StraightR");
								}
							}
						}
						else if (is_Attack == false)		//�ƹ��ൿ�� ����������
						{
							if (is_PushUp == true)
							{
								if (is_FacingLeft == true)
								{
									animator->SetCurrentAnimClip(L"Aim_UpL");
								}
								else
								{
									animator->SetCurrentAnimClip(L"Aim_UpR");
								}
							}
							else if (is_PushUp == false)
							{
								if (is_FacingLeft == true)
								{
									animator->SetCurrentAnimClip(L"IdleL");
								}
								else
								{
									animator->SetCurrentAnimClip(L"IdleR");
								}
							}
						}
					}
				}
			}
		}
	}
	else if (is_Dash == true)
	{
		if (is_FacingLeft == true)
		{
			animator->SetCurrentAnimClip(L"Dash_L");
		}
		else if (is_FacingLeft == false)
		{
			animator->SetCurrentAnimClip(L"Dash_R");
		}
	}
}

void Control::Attack(DWORD key)
{
	if (is_Dash == false)
	{
		if (Keyboard::Get()->Down(key))
		{
			shootEffectActive = true;
			shootingTime = 3.0f;
			is_Attack = true;
			ChangeAnimation();
			//bullet.push_back(new Bullet(*position+Vector3(180.0f,120.0f,0.0f), Vector3(50.0f, 20.0f, 1),2.0f, TexturePath + L"Bullet.png"));
		}
		else if (Keyboard::Get()->Press(key))
		{
			shootingTime += Time::Delta();
			if (shootingTime >= shootWaitTime)		//�տ�Ű�� ��������(����, �̵�)
			{
				for (Bullet* b : bullet)
				{
					if (b->GetActive() == false && b->GetDathAni()->GetActive() ==false)
					{
						if (is_Jump == true)
						{
							if (is_PushUp == true)
							{
								b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "jumpX", "jumpY"), 270.0f, TexturePath + L"Bullet2.png");
								b->SetActive(true);
								break;
							}
							else
							{
								if (is_FacingLeft == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "leftX", "centerY"), 0.0f, TexturePath + L"Bullet2.png");
									b->SetActive(true);
									break;
								}
								else if (is_FacingLeft == false)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "rightX", "centerY"), 0.0f, TexturePath + L"Bullet.png");
									b->SetActive(true);
									break;
								}
							}
						}
						else if (is_Aiming == true)
						{
							if (is_PushDown == true)
							{
								if (is_PushLeft == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "leftX", "diagonalDownY"), 45.0f, TexturePath + L"Bullet2.png");
									b->SetActive(true);
									break;
								}
								else if (is_PushRight == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "rightX", "diagonalDownY"), 315.0f, TexturePath + L"Bullet.png");
									b->SetActive(true);
									break;
								}
								else if (is_FacingLeft == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "DownLeftX", "downY"), 90.0f, TexturePath + L"Bullet2.png");
									b->SetActive(true);
									break;
								}
								else if (is_FacingLeft == false)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "DownRightX", "downY"), 270.0f, TexturePath + L"Bullet.png");
									b->SetActive(true);
									break;
								}
							}
							else if (is_PushUp == true)
							{
								if (is_PushLeft == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "leftX", "diagonalUpY"), 315.0f, TexturePath + L"Bullet2.png");
									b->SetActive(true);
									break;
								}
								else if (is_PushRight == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "rightX", "diagonalUpY"), 45.0f, TexturePath + L"Bullet.png");
									b->SetActive(true);
									break;
								}
								else if (is_FacingLeft == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "upLeftX", "upY"), 270.0f, TexturePath + L"Bullet2.png");
									b->SetActive(true);
									break;
								}
								else if (is_FacingLeft == false)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "upRightX", "upY"), 270.0f, TexturePath + L"Bullet2.png");
									b->SetActive(true);
									break;
								}
							}
							else
							{
								if (is_FacingLeft == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "leftX", "centerY"), 0.0f, TexturePath + L"Bullet2.png");
									b->SetActive(true);
									break;
								}
								else if (is_FacingLeft == false)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "rightX", "centerY"), 0.0f, TexturePath + L"Bullet.png");
									b->SetActive(true);
									break;
								}
							}
						}
						else
						{
							if (is_Duck == true)
							{
								if (is_FacingLeft == true)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "leftX", "duckY"), 0.0f, TexturePath + L"Bullet2.png");
									b->SetActive(true);
									break;
								}
								else if (is_FacingLeft == false)
								{
									b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "rightX", "duckY"), 0.0f, TexturePath + L"Bullet.png");
									b->SetActive(true);
									break;
								}
							}
							else if (is_Move == true)
							{
								if (is_PushUp == true)
								{
									if (is_PushLeft == true)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "leftX", "diagonalUpY"), 315.0f, TexturePath + L"Bullet2.png");
										b->SetActive(true);
										break;
									}
									else if (is_PushRight == true)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "rightX", "diagonalUpY"), 45.0f, TexturePath + L"Bullet.png");
										b->SetActive(true);
										break;
									}
									else if (is_FacingLeft == true)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "upLeftX", "upY"), 270.0f, TexturePath + L"Bullet2.png");
										b->SetActive(true);
										break;
									}
									else if (is_FacingLeft == false)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "upRightX", "upY"), 270.0f, TexturePath + L"Bullet.png");
										b->SetActive(true);
										break;
									}
								}
								else
								{
									if (is_PushLeft == true)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "leftX", "moveShootY"), 0.0f, TexturePath + L"Bullet2.png");
										b->SetActive(true);
										break;
									}
									else if (is_PushRight == true)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "rightX", "moveShootY"), 0.0f, TexturePath + L"Bullet.png");
										b->SetActive(true);
										break;
									}
								}
							}
							else
							{
								if (is_PushUp == true)
								{
									if (is_FacingLeft == true)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "upLeftX", "upY"), 270.0f, TexturePath + L"Bullet2.png");
										b->SetActive(true);
										break;
									}
									else if (is_FacingLeft == false)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "upRightX", "upY"), 270.0f, TexturePath + L"Bullet2.png");
										b->SetActive(true);
										break;
									}
								}
								else
								{
									if (is_FacingLeft == true)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "leftX", "centerY"), 0.0f, TexturePath + L"Bullet2.png");
										b->SetActive(true);
										break;
									}
									else if (is_FacingLeft == false)
									{
										b->SetPlayerBulletInfo(bulletPosition->GetShootPosition(*position, "rightX", "centerY"), 0.0f, TexturePath + L"Bullet.png");
										b->SetActive(true);
										break;
									}
								}
							}
						}
					}
				}
				//if (is_PushDown == true && is_Aiming == true)		//C������ �Ʒ���ư�� �Բ� ������
				//{
				//	shootPosY_Right = 120.0f;
				//	shootPosY_Left = 120.0f;
				//	if (is_Jump == false)
				//	{
				//		if (is_PushRight == true)		// C+�����ʾƷ�
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(300 , 80, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png", 315.0f));
				//		}
				//		else if (is_PushLeft == true)	// C+���ʾƷ�
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(160, 80, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet2.png", 45.0f));
				//		}
				//		else if (is_FacingLeft == false)  // C+�����ʺ� ������ �Ʒ�
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(255, 60, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png", 270.0f));
				//		}
				//		else if (is_FacingLeft == true)  // C+���ʺ� ������ �Ʒ�
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(195, 60, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet2.png", 90.0f));
				//		}
				//	}
				//}
				//else if (is_Duck == true)
				//{
				//	if (is_FacingLeft == false)			//�������·� �����ʺ���
				//	{
				//		bullet.push_back(new Bullet(*position + Vector3(shootPosX_Right + 50.0f, 80, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png"));
				//	}
				//	else if (is_FacingLeft == true)		//�������·� ���ʺ���
				//	{
				//		bullet.push_back(new Bullet(*position + Vector3(shootPosY_Right - 20.0f, shootPosY_Left - 40.0f, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet2.png"));
				//	}
				//}
				//else if (is_PushUp == false)
				//{
				//	if (is_Move == false)
				//	{
				//		if (is_FacingLeft == false)		//�����ʺ����·� ���
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(300, 120, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png"));
				//			shootPosY_Right = 120.0f;
				//		}
				//		else if (is_FacingLeft == true)		//���ʺ����·� ���
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(160, 120, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet2.png"));
				//			shootPosY_Left = 120.0f;
				//		}
				//	}
				//	else if (is_Move == true)		
				//	{
				//		if (is_FacingLeft == false)			//�����̸鼭 �����ʺ���
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(300, 110, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png"));
				//			shootPosY_Right = 110.0f;
				//		}
				//		else if (is_FacingLeft == true)		//�����̸鼭 ���ʺ���
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(160, 110, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet2.png"));
				//			shootPosY_Left = 110.0f;
				//		}
				//	}
				//}
				//else if (is_PushUp == true)		//����ȭ��ǥ �������ִ���
				//{
				//	shootPosY_Right = 120.0f;
				//	shootPosY_Left = 120.0f;
				//	if (is_Jump == true)		//������ ���� ����
				//	{
				//		bullet.push_back(new Bullet(*position + Vector3(220, shootPosY_Right + 50.0f, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png", 90.0f));
				//	}
				//	else if (is_Jump == false)		
				//	{
				//		if (is_PushRight == true)		//������ ������
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(300, 180, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png", 45.0f));
				//		}
				//		else if (is_PushLeft == true)		//������ ����
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(shootPosX_Left - 50.0f, shootPosY_Left + 60.0f, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet2.png", 315.0f));
				//		}
				//		else if (is_FacingLeft == false)	//�����ʔN�� �� ����
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(250, 200, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet.png", 90.0f));
				//		}
				//		else if (is_FacingLeft == true)		//���������� ����
				//		{
				//			bullet.push_back(new Bullet(*position + Vector3(200, 200, 0.0f), Vector3(80.0f, 20.0f, 1), shootSpeed, TexturePath + L"Bullet2.png", 270.0f));
				//		}
				//	}
				//}
				shootingTime = 0.0f;
			}
		}
		else if (Keyboard::Get()->Up(key))
		{
			is_Attack = false;
			shootEffectActive = false;
			ChangeAnimation();
		}
	}
}

void Control::Skiil(DWORD key, DWORD key2)
{
	if (Keyboard::Get()->Press(key))
	{
		if (is_FacingLeft == true)
			animator->SetCurrentAnimClip(L"Skill1L");
		else
			animator->SetCurrentAnimClip(L"Skill1R");
	}

	if (Keyboard::Get()->Press(key2))
	{
		if (is_FacingLeft == true)
			animator->SetCurrentAnimClip(L"Skill2L");
		else
			animator->SetCurrentAnimClip(L"Skill2R");
	}
	
}

void Control::OBB()
{
	for (Bullet* b : bullet)
	{
	
		if (b->GetActive() && b->GetDathAni()->GetActive() == false)
		{
			if (b->GetAnimRect()->GetObb()->GetTransform()->edge.LT.x > 1)		// ������ edge���� �����Ⱚ0.9999�� ���Ƿ� �����ÿ��� ������ ���ϱ����� ���
			{
				if (potato != nullptr && potato->GetIsDeath() == false && potato->GetActive() == true
					&& OBB::CheckIntersect(b->GetAnimRect()->GetObb(), potato->GetHitBox()->GetAnimRect()->GetObb()))
				{
					b->GetDathAni()->GetAnimRect()->SetPosition(*b->GetAnimRect()->GetPosition());
					b->GetDathAni()->SetActive(true);
					b->SetActive(false);
					potato->Hit(b->GetDamage());
				}
				if (onion != nullptr && onion->GetIsDeath() == false && onion->GetActive() == true
					&& OBB::CheckIntersect(b->GetAnimRect()->GetObb(), onion->GetHitBox()->GetAnimRect()->GetObb()))
				{
					b->GetDathAni()->GetAnimRect()->SetPosition(*b->GetAnimRect()->GetPosition());
					b->GetDathAni()->SetActive(true);
					b->SetActive(false);
					onion->Hit(b->GetDamage());
				}
				if (carrot != nullptr && carrot->GetIsDeath() == false && carrot->GetActive() == true
					&& OBB::CheckIntersect(b->GetAnimRect()->GetObb(), carrot->GetHitBox()->GetAnimRect()->GetObb()))
				{
					b->GetDathAni()->GetAnimRect()->SetPosition(*b->GetAnimRect()->GetPosition());
					b->GetDathAni()->SetActive(true);
					b->SetActive(false);
					carrot->Hit(b->GetDamage());
				}
			}
		}
	}
	for (Bullet* b : bullet)
	{
		if (b->GetAnimRect()->GetObb()->GetTransform()->edge.LT.x > 1)		
		{
			for (int i = 0; i < 5; i++)
			{
				if (carrot->GetMissile(i)->GetActive() == true
					&& OBB::CheckIntersect(b->GetAnimRect()->GetObb(), carrot->GetMissile(i)->GetHitBox()->GetAnimRect()->GetObb()))
				{
					b->SetActive(false);
					carrot->GetMissile(i)->SetHitBullet(b->GetDamage());
				}
			}
		}
	}
}

BulletPosition::BulletPosition()
{
	positionData.insert(make_pair("leftX", 160.0f));
	positionData.insert(make_pair("rightX", 290.0f));       //�⺻, �̵��� X

	positionData.insert(make_pair("jumpX", 220.0f));

	positionData.insert(make_pair("upLeftX", 200.0f));
	positionData.insert(make_pair("upRightX", 250.0f));
	positionData.insert(make_pair("DownLeftX", 195.0f));
	positionData.insert(make_pair("DownRightX", 255.0f));		//�� �Ʒ� �⺻ x��ǥ

	positionData.insert(make_pair("centerY", 120.0f));
	positionData.insert(make_pair("moveShootY", 110.0f));		//�⺻, �̵��� Y��ǥ
	positionData.insert(make_pair("jumpY", 170.0f));			//������ ���Ǵ� �Ʒ��� �� XY��ǥ

	positionData.insert(make_pair("diagonalUpY", 170.0f));
	positionData.insert(make_pair("diagonalDownY", 80.0f));		//�밢�� ��� Y��ǥ

	positionData.insert(make_pair("duckY", 80.0f));				//�ɾ� ���ݽ� Y��ǥ.

	positionData.insert(make_pair("upY", 200.0f));
	positionData.insert(make_pair("downY", 60.0f));
}
