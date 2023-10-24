#include "Notifies/CAnimNotify_HideWeapon.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"

FString UCAnimNotify_HideWeapon::GetNotifyName_Implementation() const
{
	return "HideWeapon";
}

void UCAnimNotify_HideWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(WeaponComponent);
	CheckNull(WeaponComponent->GetAttachment());

	WeaponComponent->GetAttachment()->SetActorHiddenInGame(true);
}
