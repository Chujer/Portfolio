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
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuaser, InOther);
	UCGravityComponent* gravityComponent = CHelpers::GetComponent<UCGravityComponent>(InAttacker);
	CheckNull(gravityComponent);
	CheckFalse(State.Get()->IsAirComboMode());
	
	gravityComponent->ResetGravityTime();
	

	for(ACharacter* target : Hitted)
	{

		UCGravityComponent* gravity = CHelpers::GetComponent<UCGravityComponent>(target);
		gravity->ResetGravityTime();
	}
}
