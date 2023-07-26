#include "Weapon/DoAction/Combo_AirCombo.h"
#include "Global.h"
#include "Components/CGravityComponent.h"

void UCombo_AirCombo::DoAction()
{
	Super::DoAction();

	UCGravityComponent* gravityComponent = CHelpers::GetComponent<UCGravityComponent>(OwnerCharacter);
	gravityComponent->StartZeroGravity();
}

void UCombo_AirCombo::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuaser, InOther);

	UCGravityComponent* charactergravity = CHelpers::GetComponent<UCGravityComponent>(InAttacker);
	charactergravity->ResetGravityTime();

	for(ACharacter* target : Hitted)
	{
		UCGravityComponent* gravity = CHelpers::GetComponent<UCGravityComponent>(target);
		gravity->ResetGravityTime();
	}
}
