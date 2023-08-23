#include "Notifies/CAnimNotify_DoIdentity.h"
#include "Global.h"
#include "Components/CIdentityComponent.h"
#include "Components/CWeaponComponent.h"
#include "Identity/CIdentity.h"

FString UCAnimNotify_DoIdentity::GetNotifyName_Implementation() const
{
	return "DoIdentity";
}

void UCAnimNotify_DoIdentity::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());

	CheckNull(weaponComponent);
	CheckNull(weaponComponent->GetAttachment());


	UCIdentity* identity;
	identity = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner())->GetAttachment()->GetIdentity();
	CheckNull(identity);
	identity->DoIdentity();
}
