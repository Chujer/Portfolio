#include "Skill/CSkill_Nomal.h"

#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Weapon/CAttachment.h"

void UCSkill_Nomal::OnAttachmentEndCollision()
{
	Super::OnAttachmentEndCollision();

	Hitted.Empty();
}

void UCSkill_Nomal::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuaser, InOther);

	CheckNull(InOther);
	

	for (ACharacter* hitted : Hitted)
	{
		CheckTrue(hitted == InOther);
	}

	Hitted.AddUnique(InOther);
	//공격 판정
	IICharacter* HitActor;
	HitActor = Cast<IICharacter>(InOther);
	HitActor->ApplyDamage(InAttacker, InAttackCuaser, SkillData.DamageType, SkillData.Power);
	HitActor->LaunchTarget(InOther, SkillData.Launch);
}

void UCSkill_Nomal::End_Skill_Implementation()
{
	Super::End_Skill_Implementation();

	Attachment->OnAttachmentBeginOverlap.Remove(this, "OnAttachmentBeginOverlap");
	Attachment->OnAttachmentEndCollision.Remove(this, "OnAttachmentEndCollision");
	
}

void UCSkill_Nomal::Pressed()
{
	CheckFalse(StateComponent->IsIdleMode());

	Super::Pressed();

	PlayMontage();
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &UCSkill_Nomal::OnAttachmentBeginOverlap);
	Attachment->OnAttachmentEndCollision.AddDynamic(this, &UCSkill_Nomal::OnAttachmentEndCollision);

}

void UCSkill_Nomal::Released()
{
	Super::Released();

}
