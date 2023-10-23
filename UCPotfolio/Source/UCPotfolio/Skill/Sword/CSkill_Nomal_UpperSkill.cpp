#include "Skill/Sword/CSkill_Nomal_UpperSkill.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/CGravityComponent.h"
#include "GameFramework/Character.h"

UCSkill_Nomal_UpperSkill::UCSkill_Nomal_UpperSkill()
{
	LaunchVector = FVector(0, 0, UpLaunchScale);
}

void UCSkill_Nomal_UpperSkill::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser,
                                                        ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuaser, InOther);
	Character->LaunchCharacter(LaunchVector, false, true);
	CHelpers::GetComponent<UCGravityComponent>(Character)->StartZeroGravity();
	
	for (ACharacter* target : Hitted)
	{
		CHelpers::GetComponent<UCGravityComponent>(target)->StartZeroGravity();
		target->LaunchCharacter(LaunchVector, true, false);
	}
}
