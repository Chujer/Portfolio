#include "Skill/CSkill_Sword01.h"

#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Weapon/CAttachment.h"

void UCSkill_Sword01::OnAttachmentEndCollision()
{
	Super::OnAttachmentEndCollision();
	
}

void UCSkill_Sword01::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
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

void UCSkill_Sword01::End_Skill_Implementation()
{
	Super::End_Skill_Implementation();

	Attachment->OnAttachmentBeginOverlap.RemoveDynamic(this, &UCSkill_Sword01::OnAttachmentBeginOverlap);
}

void UCSkill_Sword01::Pressed()
{
	CheckFalse(StateComponent->IsIdleMode());

	Super::Pressed();

	PlayMontage();
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &UCSkill_Sword01::OnAttachmentBeginOverlap);
}

void UCSkill_Sword01::Released()
{
	Super::Released();

}
