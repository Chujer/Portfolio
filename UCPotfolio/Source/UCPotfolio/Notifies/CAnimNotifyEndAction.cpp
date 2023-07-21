#include "Notifies/CAnimNotifyEndAction.h"
#include "Global.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"

FString UCAnimNotifyEndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAnimNotifyEndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCStateComponent* stateComponent = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	UCMovementComponent* movementComponent = CHelpers::GetComponent<UCMovementComponent>(MeshComp->GetOwner());

	CheckNull(stateComponent);
	CheckNull(movementComponent);

	stateComponent->SetIdleMode();

	movementComponent->Move();
	movementComponent->DisableFixedCamera();

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComponent);
	//CheckNull(weaponComponent->GetAttachment());

	CheckNull(weaponComponent->GetCurrentSkill());

	weaponComponent->GetCurrentSkill()->End_Skill_Implementation();
	weaponComponent->GetAttachment()->ClearCurrentSkill();
}
