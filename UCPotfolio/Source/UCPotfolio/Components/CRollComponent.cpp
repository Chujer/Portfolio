#include "Components/CRollComponent.h"

#include "CMovementComponent.h"
#include "CParkourComponent.h"
#include "CStateComponent.h"
#include "CWeaponComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"
#include "Utilities/CLog.h"
#include "Kismet/KismetMathLibrary.h"
#include "Skill/CSkill.h"
#include "Weapon/CDoAction.h"

UCRollComponent::UCRollComponent()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	PrimaryComponentTick.bCanEverTick = true;
}


void UCRollComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCRollComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UCRollComponent::Roll()
{
	CheckTrue(CHelpers::GetComponent<UCParkourComponent>(OwnerCharacter)->IsExecuting());

	FVector direction = FVector::ZeroVector;

	direction.X = OwnerCharacter->GetInputAxisValue("MoveForward");
	direction.Y = OwnerCharacter->GetInputAxisValue("MoveRight");

	FRotator rotate = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, direction);

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter.Get());
	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(OwnerCharacter.Get());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter.Get());

	CheckNull(weapon);
	CheckNull(movement);
	CheckNull(state);
	CheckTrue(state->IsRollMode());

	movement->Stop();

	weapon->Cansle();


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


