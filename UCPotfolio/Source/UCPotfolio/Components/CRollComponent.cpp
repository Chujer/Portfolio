#include "Components/CRollComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerInput.h"
#include "Utilities/CLog.h"

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
	FVector2D direction;
	direction.X = OwnerCharacter->GetInputAxisValue("MoveForward");
	direction.Y = OwnerCharacter->GetInputAxisValue("MoveRight");
	
	CLog::Print(FVector(direction.X, direction.Y, 0), 1);

	if (direction.Y > direction.X)
		RollDirection = ERollDirection::Right;
	else if (direction.Y < direction.X)
		RollDirection = ERollDirection::Left;
	else if (direction.X > direction.Y)
		RollDirection = ERollDirection::Front;
	else if (direction.X < direction.Y)
		RollDirection = ERollDirection::Back;
	CLog::Print((int32)RollDirection, 2);
}


