#include "Notifies/CAnimNotify_EndAction.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Weapon/CDoAction.h"

FString UCAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "End_DoAction";
}

void UCAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComponent);
	CheckNull(weaponComponent->GetDoAction());

	weaponComponent->GetDoAction()->End_DoAction();
}
