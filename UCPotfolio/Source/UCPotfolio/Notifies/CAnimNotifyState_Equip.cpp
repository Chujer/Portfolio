#include "Notifies/CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CWeaponComponent.h"
#include "Weapon/CAttachment.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());

	CheckNull(weaponComponent);
	CheckNull(weaponComponent->GetAttachment());

	weaponComponent->GetAttachment()->OnBeginEquip();

	UCStateComponent* stateComponent = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(stateComponent);
	stateComponent->SetEquipMode();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCStateComponent* stateComponent = CHelpers::GetComponent<UCStateComponent>(MeshComp->GetOwner());
	CheckNull(stateComponent);
	stateComponent->SetIdleMode();
}
