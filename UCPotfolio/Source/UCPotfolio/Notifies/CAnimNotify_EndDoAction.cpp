#include "Notifies/CAnimNotify_EndDoAction.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Skill/CSkill.h"
#include "Weapon/CAttachment.h"
#include "Weapon/CDoAction.h"

FString UCAnimNotify_EndDoAction::GetNotifyName_Implementation() const
{
	return "End_Do_Action";
}

void UCAnimNotify_EndDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComponent);
	bool test = weaponComponent->GetDoAction();
	CheckNull(weaponComponent->GetDoAction());

	if (!!weaponComponent->GetCurrentSkill())
	{
		weaponComponent->GetCurrentSkill()->End_Skill_Implementation();
		weaponComponent->GetAttachment()->ClearCurrentSkill();
	}

	weaponComponent->GetDoAction()->End_DoAction();
}
