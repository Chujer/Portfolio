#include "Characters/AnimInstances/CAnimInstance_Base.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/CCharacter_Base.h"
#include "Kismet/KismetMathLibrary.h"

void UCAnimInstance_Base::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACCharacter_Base>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
}

void UCAnimInstance_Base::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	//bDown = OwnerCharacter->GetIsDown();

	Speed = OwnerCharacter->GetVelocity().Size2D();

	FRotator rotator = OwnerCharacter->GetVelocity().ToOrientationRotator();
	FRotator rotator2 = OwnerCharacter->GetControlRotation();
	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2);
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, DeltaSeconds, 25);
	Direction = PrevRotation.Yaw;

	Pitch = UKismetMathLibrary::FInterpTo(Pitch, OwnerCharacter->GetBaseAimRotation().Pitch, DeltaSeconds, 25);

	bFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();

	//다운상태
	if(bDown)
	{
		DownTime += DeltaSeconds;
		if(DownTime > MaxDownTime)
		{
			bDown = false;
			OwnerCharacter->SetIsDown(false);
			DownTime = 0;
			//기상 애니메이션 재생
			if (DownDirection > 0)
			{
				OwnerCharacter->PlayAnimMontage(BackWakeupMontage);
			}
			else
				OwnerCharacter->PlayAnimMontage(FrontWakeupMontage);
		}
	}
}

void UCAnimInstance_Base::SetFrontWakeupMontage(UAnimMontage* Montage)
{
	FrontWakeupMontage = Montage;
}

void UCAnimInstance_Base::SetBackWakeupMontage(UAnimMontage* Montage)
{
	BackWakeupMontage = Montage;
}

void UCAnimInstance_Base::SetDownDirection(float InDownDirection)
{
	CheckTrue(InDownDirection > 1 || InDownDirection < -1);
	this->DownDirection = InDownDirection;
	bDown = true;
}

void UCAnimInstance_Base::ResetDownTime()
{
	DownTime = 0;
}
