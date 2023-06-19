#include "Weapon/CWeaponStructures.h"
#include "Utilities/CLog.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

void FHitData::PlayHitMontage(ACharacter* InCharacter)
{
	CheckNull(InCharacter);
	

	int32 Index = UKismetMathLibrary::RandomInteger((int32)EDamageType::MAX -1);
	CheckNull(Montage[Index]);

	InCharacter->PlayAnimMontage(Montage[Index], PlayRate);
}

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

	movement->SetUseControllYaw()
}

void FDoActionData::LaunchCharacter(class ACharacter* InSelf, class ACharacter* LaunchCharacter)
{
	CheckNull(LaunchCharacter);
	CheckNull(InSelf);

	FVector launchVelocity = InSelf->GetActorForwardVector() * Launch.X;
	launchVelocity.Z = Launch.Y;


	LaunchCharacter->LaunchCharacter(launchVelocity, false, false);

	//�����ڵ� �Բ� ��ġ
	CheckFalse(bWithLaunch);
	//InSelf->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InSelf->LaunchCharacter(launchVelocity, false, false);
}
