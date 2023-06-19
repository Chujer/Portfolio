#include "Components/CRollComponent.h"

#include "CMovementComponent.h"
#include "CStateComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"
#include "Utilities/CLog.h"
#include "Kismet/KismetMathLibrary.h"

UCRollComponent::UCRollComponent()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


void UCRollComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCRollComponent::Roll()
{
	FVector direction = FVector::ZeroVector;

	direction.X = OwnerCharacter->GetInputAxisValue("MoveForward");
	direction.Y = OwnerCharacter->GetInputAxisValue("MoveRight");

	FRotator rotate = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, direction);

	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(OwnerCharacter);
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	CheckNull(movement);
	CheckNull(state);

	CheckTrue(state->IsRollMode());

	movement->Stop();

	if (rotate.Yaw == -90.0f) // аб
	{
		EDirection = ERollDirection::Left;
	}
	else if (rotate.Yaw == 90.0f) // ©Л
	{
		EDirection = ERollDirection::Right;
	}
	else if (abs(rotate.Yaw) < 90.0f) // ╬у
	{
		EDirection = ERollDirection::Front;
		movement->SetUseControllYaw(false);
	}
	else if (abs(rotate.Yaw) > 90.0f) // ╣з
	{
		EDirection = ERollDirection::Back;
		movement->SetUseControllYaw(false);
		rotate.Yaw += 180;
	}

	OwnerCharacter->SetActorRotation(OwnerCharacter->GetActorRotation() + rotate);

	OwnerCharacter->PlayAnimMontage(RollMontage[(int32)EDirection], 1.0f);
	state->SetRollMode();
}


