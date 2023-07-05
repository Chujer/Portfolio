#include "Skill/Sword/CHaveAction_SwordFlashSlash.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Characters/CPlayer.h"
#include "Utilities/CLog.h"

void UCHaveAction_SwordFlashSlash::Begin_Skill_Implementation()
{
	Super::Begin_Skill_Implementation();
}

void UCHaveAction_SwordFlashSlash::SkillAction1()
{
	Super::SkillAction1();


}

void UCHaveAction_SwordFlashSlash::Pressed()
{
	Super::Pressed();
	CLog::Print("SwordFlashSlash : Pressed : " + IsChargeEnd,1);
	PlayMontage();
}

void UCHaveAction_SwordFlashSlash::Released()
{
	ChargeTime = false;
	IsChargeEnd = false;
	CLog::Print("SwordFlashSlash : Released : " + IsChargeEnd,2);
	Super::Released();
}

void UCHaveAction_SwordFlashSlash::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Tick�� CurrentSkill�� ��������� Released�� ���� �������� ����
	ChargeTime += DeltaSeconds;

	if (ChargeTime > MaxChargeTime)
	{
		IsChargeEnd = true;
		CLog::Print("SwordFlashSlash : Tick : " + IsChargeEnd,3);
	}

}
