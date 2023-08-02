#include "Weapon/DoAction/Combo_AirCombo.h"
#include "Global.h"
#include "Components/CGravityComponent.h"
#include "Components/CStateComponent.h"

void UCombo_AirCombo::BeginPlay(ACharacter* InOwner, const TArray<FDoActionData>& InDoActionDatas)
{
	Super::BeginPlay(InOwner, InDoActionDatas);
}

void UCombo_AirCombo::DoAction()
{
	UCDoAction_Combo::DoAction();  
	CheckFalse(State->IsIdleMode());

	UCGravityComponent* gravityComponent = CHelpers::GetComponent<UCGravityComponent>(OwnerCharacter);
	gravityComponent->StartZeroGravity();
}

void UCombo_AirCombo::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	CheckTrue(State->IsSkillMode());
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuaser, InOther);
	UCGravityComponent* gravityComponent = CHelpers::GetComponent<UCGravityComponent>(InAttacker);
	CheckNull(gravityComponent);
	CheckFalse(State.Get()->IsAirComboMode());

	//공중콤보 마지막 공격일시 중력및 가속도 초기화를하지않음
	if(Index == DoActionDatas.Num() - 1)
	{
		//if(gravityComponent->OnEndZeroGravity.IsBound())
		//	gravityComponent->OnEndZeroGravity.Broadcast();
	}
	else
	{
		gravityComponent->ResetGravityTime();


		for (ACharacter* target : Hitted)
		{
			UCGravityComponent* gravity = CHelpers::GetComponent<UCGravityComponent>(target);
			gravity->ResetGravityTime();
		}
	}
		
}
