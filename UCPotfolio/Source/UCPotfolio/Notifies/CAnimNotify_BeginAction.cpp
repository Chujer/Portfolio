#include "Notifies/CAnimNotify_BeginAction.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Weapon/CDoAction.h"

FString UCAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "Begin_DoAction";
}

void UCAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComponent);
	CheckNull(weaponComponent->GetDoAction());

	weaponComponent->GetDoAction()->Begin_DoAction();
}
