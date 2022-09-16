#include "stdafx.h"
#include "Test.h"

#include "Game/Player.h"
//#include "Game/HitBox.h"
#include "Game/Mob_Potato.h"
#include "Game/Mob_Onion.h"
#include "Game/Mob_Carrot.h"
#include "Game/Effect.h"


void Test::Init()
{
	player = new Player({ 75, 60, 0 }, { 450, 250, 1 });
	hitbox = new Mob_Potato({ 700, 100, 0 }, { 720, 670, 1 }, player->GetHitBox(), true);
	hitbox2 = new Mob_Onion({ 430, 70, 0 }, { 450, 500, 1 }, player->GetHitBox(), false);
	hitbox3 = new Mob_Carrot({ 250, 170, 0 }, { 800, 660, 1 }, player->GetHitBox(), false);
	ground = new Effect({ 0,0,0 }, { WinMaxWidth,WinMaxHeight,1 }, L"BackGround");
	ground2 = new Effect({ 0,0,0 }, { WinMaxWidth,WinMaxHeight,1 }, L"BackGround_Front");
	hpUI = new Effect({ 20,20,0 }, { 80,30,1 }, L"UI_HP3");
	log = new Effect({ 0,0,0 }, { WinMaxWidth,WinMaxHeight,1 }, L"InOut");
	player->SetMob_Potato(hitbox);
	player->SetMob_Onion(hitbox2);
	player->SetMob_Carrot(hitbox3);
}
/*
1. ���ݵ��� ����
���ڰ���->�÷��̾�, ���İ���->�÷��̾�, ���->�÷��̾�, �÷��̾� ��->���, ��ٺ�->�÷��̾�

bullet->character

bullet���� ����?
obb(target, tex)
 Hit(damage);
2�ð�

 2. �÷��̾� �뽬 ����
 ?�ð�

 3. �÷��̾� ��Ʈ�� �����ð� ���� �� ����
 30��

 4. ���� �ִϸ��̼� ����

 5. �÷��̾� ������ ��Ʈ�ڽ� ���̱�
----------------------------------------------
6��
1. �÷��̾� ���ݽ� ����Ʈ
2. �÷��̾� ���� ���� ��Ʈ�� ����Ʈ
3. �÷��̾� ��Ʈ�� �ִϸ��̼�
4. �÷��̾� �뽬 ����Ʈ
5. ���� ���ݽ� ����Ʈ
6. ���� ����� ����Ʈ -> �̹���x
*/

void Test::Destroy()
{
	SAFE_DELETE(player);
	SAFE_DELETE(hitbox);
	SAFE_DELETE(hitbox2);
	SAFE_DELETE(hitbox3);
	SAFE_DELETE(ground);
	SAFE_DELETE(ground2);
	SAFE_DELETE(log);
}

void Test::Update()
{

	if (player->GetHit() == false && player->GetHP() > 0)
	{
		if (hitbox->OBB() || hitbox2->OBB() || hitbox3->OBB())
		{
			player->SetHit();
			player->GetHP();

		}
	}
	player->Update();
	player->Move();

	if (hitbox->GetActive() && hitbox->GetIsDeath() == false && ObbCharacterCheck(player->GetHitBox(), hitbox->GetHitBox())
		|| hitbox2->GetActive() && hitbox2->GetIsDeath() == false && ObbCharacterCheck(player->GetHitBox(), hitbox2->GetHitBox()))		// �÷��̾�� ���� �浹��
	{
		if (player->GetHit() == false)
		{
			player->GetHP();
			player->SetHit();
		}
	}

	if (Keyboard::Get()->Down(VK_SPACE))
	{
		if (hitbox->GetActive() == true)
			hitbox->SetHp();
		else if (hitbox2->GetActive() == true)
			hitbox2->SetHp();
		else if (hitbox3->GetActive() == true)
			hitbox3->SetHp();
	}
	
	
	if (hitbox->GetNextMob() == true && hitbox2->GetIsDeath() == false)
		hitbox2->SetActive(true);
	if (hitbox2->GetNextMob() == true)
		hitbox3->SetActive(true);

	if (hitbox3->getHp() < 1)
		gameInfo = END;

	if(hitbox->GetActive()==true)
		hitbox->Update();
	if(hitbox2->GetActive()==true)
		hitbox2->Update();
	if (hitbox3->GetActive() == true && hitbox != nullptr)
		hitbox3->Update();

	if (player->GetHP() == 2)
		hpUI->GetAnimator()->SetCurrentAnimClip(L"UI_HP2");
	else if (player->GetHP() == 1)
		hpUI->GetAnimator()->SetCurrentAnimClip(L"UI_HP1");
	else if (player->GetHP() < 1)
		hpUI->GetAnimator()->SetCurrentAnimClip(L"UI_HP_DEATH");

	if (gameInfo == GAME_INTRO)
	{
		if(log->GetAnimator()->GetEndAni(L"InOut"))
			log->GetAnimator()->SetCurrentAnimClip(L"Ready");
		if (log->GetAnimator()->GetEndAni(L"Ready"))
			log->GetAnimator()->SetCurrentAnimClip(L"Wallop");
		if (log->GetAnimator()->GetEndAni(L"Wallop"))
			gameInfo = PLAY;
	}
	else if (gameInfo == END)
	{
		if (log->GetAnimator()->GetClipName() == L"Wallop")
			log->GetAnimator()->SetCurrentAnimClip(L"FightText_KO");
		if (log->GetAnimator()->GetEndAni(L"FightText_KO"))
			log->GetAnimator()->SetCurrentAnimClip(L"OutIn");
		if (log->GetAnimator()->GetEndAni(L"OutIn"))
			log->GetAnimator()->SetCurrentAnimClip(L"Black");
	}

	player->PlayerBulletOBB();		// �÷��̾����->����
	ground->Update();
	ground2->Update();

	hpUI->Update();
	if(gameInfo!=PLAY)
		log->Update();
}

void Test::Render()
{
	if (hitbox3->GetActive() == true && hitbox != nullptr)
		hitbox3->Render();

	if(hitbox3->GetActive()==false||hitbox3->GetIsDeath())
		ground->Render();

	if (hitbox->GetActive() == true)
		hitbox->Render();
	if (hitbox2->GetActive() == true)
		hitbox2->Render();
	player->Render();

	ground2->Render();
	hpUI->Render();
	if (gameInfo != PLAY)
		log->Render();
}

void Test::PostRender()
{
}

void Test::GUI()
{
}
