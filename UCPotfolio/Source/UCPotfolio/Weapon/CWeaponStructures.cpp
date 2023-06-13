#include "Weapon/CWeaponStructures.h"
#include "Utilities/CLog.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CMovementComponent.h"
#include "Animation/AnimMontage.h"

void FEquipData::PlayAnim(ACharacter* InCharacter)
{
	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(InCharacter);

	if(!!movement)
	{
		bCanMove ? movement->Move() : movement->Stop();
	}

	if (!!InCharacter)
		InCharacter->PlayAnimMontage(Montage, PlayRate);
}

void FDoActionData::PlayDoAction(ACharacter* InCharacter)
{
	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(InCharacter);

	if (!!movement)
	{
		bCanMove ? movement->Move() : movement->Stop();

	}
	if (!!InCharacter && !!Montage)
	{
		InCharacter->PlayAnimMontage(Montage, PlayRate);
	}

	if (!!movement && bFixedCamera)
		movement->EnableFixedCamera();
}
