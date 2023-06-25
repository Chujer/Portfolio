#include "Skill/CSkill.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Weapon/CAttachment.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"

UCSkill::UCSkill()
{
}

void UCSkill::BeginPlay(ACPlayer* InCharacter, ACAttachment* InAttachment)
{
	Character = InCharacter;
	StateComponent = CHelpers::GetComponent<UCStateComponent>(InCharacter);
	MovementComponent = CHelpers::GetComponent<UCMovementComponent>(InCharacter);
	Attachment = InAttachment;
}

void UCSkill::PlayMontage()
{
	CheckNull(SkillData.Montage);

	Character->PlayAnimMontage(SkillData.Montage, SkillData.PlayRate);

	if(SkillData.bFixedCamera == true)
		MovementComponent->EnableFixedCamera();
}

void UCSkill::Pressed()
{
	bPressed = true;
	StateComponent->SetSkillMode();
}

void UCSkill::Released()
{
	bPressed = false;
}

