#include "Notifies/CAnimNotify_SetWeaponType.h"
#include "Global.h"

FString UCAnimNotify_SetWeaponType::GetNotifyName_Implementation() const
{
	return FString("SetWeaponType");
}

void UCAnimNotify_SetWeaponType::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComponent);
	CheckNull(weaponComponent->GetAttachment());

	weaponComponent->SetMode(WeaponType);
}
