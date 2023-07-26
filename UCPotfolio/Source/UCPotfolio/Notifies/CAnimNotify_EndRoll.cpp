#include "Notifies/CAnimNotify_EndRoll.h"
#include "Global.h"
#include "Components/CMovementComponent.h"
#include "Components/CRollComponent.h"
#include "Components/CStateComponent.h"

FString UCAnimNotify_EndRoll::GetNotifyName_Implementation() const
{
	return "EndRoll";
}

void UCAnimNotify_EndRoll::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCMovementComponent* movement;
	movement = CHelpers::GetComponent<UCMovementComponent>(MeshComp->GetOwner());

	CheckNull(movement);

	movement->SetUseControllYaw(true);
	movement->Move();

	UCStateComponent* state;
	state = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());

	CheckNull(state);

	state->SetIdleMode();

}
