#include "Notifies/CAnimNotify_SkillActionEnd.h"
#include "Components/CWeaponComponent.h"
#include "Skill/CSkill_HaveAction.h"
#include "Global.h"

FString UCAnimNotify_SkillActionEnd::GetNotifyName_Implementation() const
{
	return "SkillActionEnd";
}

void UCAnimNotify_SkillActionEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());

	CheckNull(weaponComponent);

	UCSkill_HaveAction* skill = Cast<UCSkill_HaveAction>(weaponComponent->GetCurrentSkill());

	CheckNull(skill);

	skill->EndSkillAction(Index);
}
