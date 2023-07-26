#include "Components/CMovementComponent.h"

#include "GameFramework/Character.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utilities/CLog.h"

UCMovementComponent::UCMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCMovementComponent::OnMoveForward(float InAxis)
{
	CheckFalse(bCanMove);
	
	
	FVector direction = UKismetMathLibrary::GetForwardVector(FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0));

	OwnerCharacter->AddMovementInput(direction, InAxis);

	if(InAxis < 0)	
		OffSprint();
}

void UCMovementComponent::OnMoveRight(float InAxis)
{
	CheckFalse(bCanMove);

	FVector direction = UKismetMathLibrary::GetRightVector(FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0));

	OwnerCharacter->AddMovementInput(direction, InAxis);
}

void UCMovementComponent::OnHorizontalLook(float InAxis)
{
	CheckTrue(bFixedCamera);

	OwnerCharacter->AddControllerYawInput(InAxis * HorizontalLook * GetWorld()->GetDeltaSeconds());
}

void UCMovementComponent::OnVerticallLook(float InAxis)
{
	CheckTrue(bFixedCamera);

	OwnerCharacter->AddControllerPitchInput(InAxis * VerticalLook * GetWorld()->GetDeltaSeconds());
}

void UCMovementComponent::SetUseControllYaw(bool InBool)
{
	CheckNull(OwnerCharacter);
	OwnerCharacter->bUseControllerRotationYaw = InBool;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = !InBool;
}

void UCMovementComponent::OnSprint()
{
	CheckNull(OwnerCharacter);
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 1000;
}

void UCMovementComponent::OffSprint()
{
	CheckNull(OwnerCharacter);
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = 600;
}

