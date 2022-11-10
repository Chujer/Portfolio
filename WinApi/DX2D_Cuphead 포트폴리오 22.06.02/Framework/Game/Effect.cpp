#include "Framework.h"
#include "Effect.h"

Effect::Effect(Vector3 position, Vector3 size, wstring name)
	:Character(position, size)
{
	if (name == L"BulletDeath")
		point = 2;


	Texture2D* srcTex1 = new Texture2D(TexturePath + L"/Monster/Potato/Ground1.png");			//고정땅
	Texture2D* srcTex2 = new Texture2D(TexturePath + L"/Monster/Potato/Ground2.png");			//고정땅 절반
	Texture2D* srcTex3 = new Texture2D(TexturePath + L"/Monster/IntroGround/IntroGround.png");			//땅 인트로 애니메이션
	Texture2D* srcTex4 = new Texture2D(TexturePath + L"/Monster/Onion/Tear/Tear_R.png");
	Texture2D* srcTex5 = new Texture2D(TexturePath + L"/Monster/Onion/Tear/Tear_L.png");
	Texture2D* srcTex6 = new Texture2D(TexturePath + L"Monster/Carrot/Bullet/Bullet_Beam_Ready_r.png");
	Texture2D* srcTex7 = new Texture2D(TexturePath + L"Player/ShootEffect.png");

	Texture2D* bulletDeathEffect = new Texture2D(TexturePath + L"BulletDeath.png");

	Texture2D* UI_HP3 = new Texture2D(TexturePath + L"Player/HP_UI/HP3.png");
	Texture2D* UI_HP2 = new Texture2D(TexturePath + L"Player/HP_UI/HP2.png");
	Texture2D* UI_HP1 = new Texture2D(TexturePath + L"Player/HP_UI/HP1.png");
	Texture2D* UI_HP_DEATH = new Texture2D(TexturePath + L"Player/HP_UI/DEAD.png");


	Texture2D* ground = new Texture2D(TexturePath + L"BackGround.png");
	Texture2D* ground2 = new Texture2D(TexturePath + L"Ground1.png");

	Texture2D* InOut = new Texture2D(TexturePath + L"In_Out.png");
	Texture2D* OutIn = new Texture2D(TexturePath + L"Out_In.png");
	Texture2D* Ready = new Texture2D(TexturePath + L"Ready.png");
	Texture2D* Wallop = new Texture2D(TexturePath + L"Wallop.png");
	Texture2D* FightText_KO = new Texture2D(TexturePath + L"FightText_KO.png");
	Texture2D* black = new Texture2D(TexturePath + L"Black.png");


	TextureInfo black_Info(Vector2(black->GetWidth(), black->GetHeight()), 1, 1);
	TextureInfo InOut_Info(Vector2(InOut->GetWidth(), InOut->GetHeight()), 17, 1);
	TextureInfo OutIn_Info(Vector2(OutIn->GetWidth(), OutIn->GetHeight()), 17, 1);
	TextureInfo Ready_Info(Vector2(Ready->GetWidth(), Ready->GetHeight()), 20, 1);
	TextureInfo Wallop_Info(Vector2(Wallop->GetWidth(), Wallop->GetHeight()), 30, 1);
	TextureInfo FightText_KO_Info(Vector2(FightText_KO->GetWidth(), FightText_KO->GetHeight()), 27, 1);

	TextureInfo HP3_Info(Vector2(UI_HP3->GetWidth(), UI_HP3->GetHeight()), 1, 1);
	TextureInfo HP2_Info(Vector2(UI_HP2->GetWidth(), UI_HP2->GetHeight()), 1, 1);
	TextureInfo HP1_Info(Vector2(UI_HP1->GetWidth(), UI_HP1->GetHeight()), 2, 1);
	TextureInfo HP_DEATH_Info(Vector2(UI_HP_DEATH->GetWidth(), UI_HP_DEATH->GetHeight()), 1, 1);

	TextureInfo tInfo1(Vector2(srcTex1->GetWidth(), srcTex1->GetHeight()),1,1 );
	TextureInfo tInfo2(Vector2(srcTex2->GetWidth(), srcTex2->GetHeight()),1,1 );
	TextureInfo tInfo3(Vector2(srcTex3->GetWidth(), srcTex3->GetHeight()),17,1 );

	TextureInfo tInfo4(Vector2(srcTex4->GetWidth(), srcTex4->GetHeight()),7,3 );
	TextureInfo tInfo5(Vector2(srcTex4->GetWidth(), srcTex4->GetHeight()),7,3 );
	TextureInfo tInfo6(Vector2(srcTex6->GetWidth(), srcTex6->GetHeight()),8,1 );
	TextureInfo tInfo7(Vector2(srcTex7->GetWidth(), srcTex7->GetHeight()),4,1 );

	TextureInfo groundInfo(Vector2(ground->GetWidth(), ground->GetHeight()), 1, 1);

	TextureInfo bulletDeathInfo(Vector2(bulletDeathEffect->GetWidth(), bulletDeathEffect->GetHeight()), 6, 1);

	clips.push_back(new AnimationClip(L"InOut", InOut, 17, Vector2(0, 0), Vector2(InOut_Info.scsizeX*17.0f, InOut_Info.scsizeY), 1.0f / 21.0f));
	clips.push_back(new AnimationClip(L"Black", black, 1, Vector2(0, 0), Vector2(black_Info.scsizeX, black_Info.scsizeY), 1.0f / 1.0f));
	clips.push_back(new AnimationClip(L"OutIn", OutIn, 17, Vector2(0, 0), Vector2(OutIn_Info.scsizeX*17.0f, OutIn_Info.scsizeY), 1.0f / 21.0f));
	clips.push_back(new AnimationClip(L"Ready", Ready, 20, Vector2(0, 0), Vector2(Ready_Info.scsizeX*20.0f, Ready_Info.scsizeY), 1.0f / 21.0f));
	clips.push_back(new AnimationClip(L"Wallop", Wallop, 30, Vector2(0, 0), Vector2(Wallop_Info.scsizeX*30.0f, Wallop_Info.scsizeY), 1.0f / 21.0f));
	clips.push_back(new AnimationClip(L"FightText_KO", FightText_KO, 27, Vector2(0, 0), Vector2(FightText_KO_Info.scsizeX*27.0f, FightText_KO_Info.scsizeY), 1.0f / 21.0f));

	clips.push_back(new AnimationClip(L"Ground1", srcTex1, 1, Vector2(0, 0), Vector2(tInfo1.scsizeX, tInfo1.scsizeY), 1.0f / 1.0f));
	clips.push_back(new AnimationClip(L"Ground2", srcTex2, 1, Vector2(0, 0), Vector2(tInfo2.scsizeX, tInfo2.scsizeY), 1.0f / 1.0f));
	clips.push_back(new AnimationClip(L"IntroGround", srcTex3, 17, Vector2(0, 0), Vector2(tInfo3.scsizeX*17.0f, tInfo3.scsizeY), 1.0f / 21.0f));

	clips.push_back(new AnimationClip(L"Tear_Intro_R", srcTex4, 5, Vector2(0, 0), Vector2(tInfo4.scsizeX*5.0f, tInfo4.scsizeY), 1.0f / 21.0f));
	clips.push_back(new AnimationClip(L"Tear_Loop_R", srcTex4, 4, Vector2(0, tInfo4.scsizeY), Vector2(tInfo4.scsizeX*4.0f, tInfo4.scsizeY*2.0f), 1.0f / 21.0f));
	clips.push_back(new AnimationClip(L"Tear_End_R", srcTex4, 7, Vector2(0, tInfo4.scsizeY*2.0f), Vector2(tInfo4.scsizeX*7.0f, tInfo4.scsizeY*3.0f), 1.0f / 21.0f));

	clips.push_back(new AnimationClip(L"Tear_Intro_L", srcTex5, 5, Vector2(tInfo5.scsizeX*2.0f, 0), Vector2(tInfo5.scsizeX*7.0f, tInfo5.scsizeY), 1.0f / 21.0f, true));
	clips.push_back(new AnimationClip(L"Tear_Loop_L", srcTex5, 4, Vector2(tInfo5.scsizeX*3.0f, tInfo5.scsizeY), Vector2(tInfo5.scsizeX*7.0f, tInfo5.scsizeY*2.0f), 1.0f / 21.0f, true));
	clips.push_back(new AnimationClip(L"Tear_End_L", srcTex5, 7, Vector2(0.0f, tInfo5.scsizeY*2.0f), Vector2(tInfo5.scsizeX*7.0f, tInfo5.scsizeY*3.0f), 1.0f / 21.0f, true));

	clips.push_back(new AnimationClip(L"Beam_Effect", srcTex6, 8, Vector2(0.0f, 0.0f), Vector2(tInfo6.scsizeX*8.0f, tInfo6.scsizeY), 1.0f / 21.0f));

	clips.push_back(new AnimationClip(L"player_Bullet_Effect", srcTex7, 4, Vector2(0.0f, 0.0f), Vector2(tInfo7.scsizeX*4.0f, tInfo7.scsizeY), 1.0f / 21.0f));
	
	clips.push_back(new AnimationClip(L"UI_HP3", UI_HP3, 1, Vector2(0.0f, 0.0f), Vector2(HP3_Info.scsizeX, HP3_Info.scsizeY), 1.0f / 1.0f));
	clips.push_back(new AnimationClip(L"UI_HP2", UI_HP2, 1, Vector2(0.0f, 0.0f), Vector2(HP2_Info.scsizeX, HP2_Info.scsizeY), 1.0f / 1.0f));
	clips.push_back(new AnimationClip(L"UI_HP1", UI_HP1, 2, Vector2(0.0f, 0.0f), Vector2(HP1_Info.scsizeX*2.0f, HP1_Info.scsizeY), 1.0f / 10.0f));
	clips.push_back(new AnimationClip(L"UI_HP_DEATH", UI_HP_DEATH, 1, Vector2(0.0f, 0.0f), Vector2(HP_DEATH_Info.scsizeX, HP_DEATH_Info.scsizeY), 1.0f / 1.0f));

	clips.push_back(new AnimationClip(L"BackGround", ground, 1, Vector2(0.0f, 0.0f), Vector2(groundInfo.scsizeX, groundInfo.scsizeY), 1.0f / 1.0f));
	clips.push_back(new AnimationClip(L"BackGround_Front", ground2, 1, Vector2(0.0f, 0.0f), Vector2(groundInfo.scsizeX, groundInfo.scsizeY), 1.0f / 1.0f));

	clips.push_back(new AnimationClip(L"BulletDeath", bulletDeathEffect, 6, Vector2(0.0f, 0.0f), Vector2(bulletDeathInfo.scsizeX*6.0f, bulletDeathInfo.scsizeY), 1.0f /21.0f));
	
	animator->AddAnimClips(clips);

	animator->SetCurrentAnimClip(name);

	animRect->SetAnimation(animator);
}

Effect::~Effect()
{
}

void Effect::Update()
{
	animator->Update();
	if (animator->GetEndAni(L"Tear_Intro_R"))
	{
		animator->SetCurrentAnimClip(L"Tear_Loop_R");
	}
	if (animator->GetEndAni(L"Tear_Intro_L"))
	{
		animator->SetCurrentAnimClip(L"Tear_Loop_L");
	}
	animRect->Update();
}

void Effect::Render()
{
	sb->SetPoint(point);
	sb->SetPSBuffer(0);
	animRect->Render();
}

void Effect::Move()
{
}

bool Effect::GetActive()
{
	return active;
}

void Effect::SetActive(bool active)
{
	this->active = active;
}
