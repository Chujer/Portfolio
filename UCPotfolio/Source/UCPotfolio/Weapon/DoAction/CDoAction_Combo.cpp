#include "Weapon/DoAction/CDoAction_Combo.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "Utilities/CLog.h"

UCDoAction_Combo::UCDoAction_Combo()
{
}

void UCDoAction_Combo::DoAction()
{
	CheckTrue(DoActionDatas.Num() < 1)

	if(bEnable)
	{
		bEnable = false;
		bExist = true;

		return;
	}

	CheckFalse(State->IsIdleMode());
	
	Super::DoAction();
	DoActionDatas[Index].PlayDoAction(OwnerCharacter);
}

void UCDoAction_Combo::Begin_DoAction()
{
	Super::Begin_DoAction();
	CheckFalse(bExist);

	bExist = false;
	DoActionDatas[++Index].PlayDoAction(OwnerCharacter);
}

void UCDoAction_Combo::End_DoAction()
{
	Super::End_DoAction();

	Index = 0;
}

void UCDoAction_Combo::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuaser, InOther);
	CheckTrue(State->IsSkillMode());
	CheckNull(InOther);
	CheckTrue(DoActionDatas.Num() < 1)

	for (ACharacter* hitted : Hitted)
	{
		CheckTrue(hitted == InOther);
	}

	Hitted.AddUnique(InOther);
	//공격 판정
	Cast<IICharacter>(InOther)->ApplyDamage(InAttacker, InAttackCuaser, DoActionDatas[Index].DamageType, DoActionDatas[Index].Power);
	DoActionDatas[Index].LaunchCharacter(InAttacker, InOther);
}

void UCDoAction_Combo::OnAttachmentEndCollision()
{
	Super::OnAttachmentEndCollision();

	Hitted.Empty();
}