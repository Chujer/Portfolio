#include "Notifies/BPAnimNotify_SkillAction.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"
#include "Skill/CSkill_HaveAction.h"

FString UBPAnimNotify_SkillAction::GetNotifyName_Implementation() const
{
	return "SkillAction";
}

void UBPAnimNotify_SkillAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());

	CheckNull(weaponComponent);

	UCSkill_HaveAction* skill = Cast<UCSkill_HaveAction>(weaponComponent->GetCurrentSkill());

	CheckNull(skill);

	skill->SelectSkillAction(Index);
}
