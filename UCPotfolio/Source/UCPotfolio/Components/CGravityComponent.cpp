#include "Components/CGravityComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global.h"

UCGravityComponent::UCGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCGravityComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacter>(GetOwner());

	CheckNull(Character);
	CharacterMovementComponent = Character->GetCharacterMovement();
}

void UCGravityComponent::StartZeroGravity()
{
	CharacterMovementComponent->Velocity.Z = 0;
	CharacterMovementComponent->GravityScale = 0;
	
	bZeroGravity = true;

	if (OnStartGravity.IsBound())
		OnStartGravity.Broadcast();
}

void UCGravityComponent::EndZeroGravity()
{
	GravityTime = 0;
	CharacterMovementComponent->GravityScale = 2;
	bZeroGravity = false;
	if (OnEndGravity.IsBound())
		OnEndGravity.Broadcast();
}

void UCGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bZeroGravity == true)
	{
		GravityTime += DeltaTime;
		if(ZeroGravityTime < GravityTime)
		{
			EndZeroGravity();
		}
	}
}

