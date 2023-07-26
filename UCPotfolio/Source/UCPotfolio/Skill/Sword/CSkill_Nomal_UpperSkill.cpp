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
	CHelpers::GetComponent<UCGravityComponent>(Cast<AActor>(Character))->StartZeroGravity();
	Character->LaunchCharacter(LaunchVector, false, true);

	for(ACharacter* target : Hitted)
	{
		CHelpers::GetComponent<UCGravityComponent>(target)->StartZeroGravity();
		target->LaunchCharacter(LaunchVector, true, false);
	}
	
}
