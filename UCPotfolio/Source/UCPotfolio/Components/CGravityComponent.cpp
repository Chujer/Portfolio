#include "Components/CGravityComponent.h"

#include "CStateComponent.h"
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
	Character->LandedDelegate.AddDynamic(this, &UCGravityComponent::OnLanded);
}

void UCGravityComponent::StartZeroGravity()
{
	CharacterMovementComponent->Velocity.Z = 0;
	CharacterMovementComponent->GravityScale = 0;

	GravityTime = 0;
	bZeroGravity = true;

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(Character);
	CheckNull(state);
	state->OnAirComboMode();
	if (OnStartZeroGravity.IsBound())
		OnStartZeroGravity.Broadcast();
}

void UCGravityComponent::ResetGravityTime()
{
	GravityTime = 0;
	bZeroGravity = true;
	CharacterMovementComponent->Velocity.Z = 0;
	CharacterMovementComponent->GravityScale = 0;


	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(Character);
	CheckNull(state);
	state->OnAirComboMode();
}

void UCGravityComponent::EndZeroGravity()
{
	bZeroGravity = false;
	GravityTime = 0;
	CharacterMovementComponent->GravityScale = 1;
}

void UCGravityComponent::OnLanded(const FHitResult& Hit)
{
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(Character);
	CheckNull(state);
	CheckFalse(state->IsAirComboMode());

	state->SetIdleMode();
	state->OffAirComboMode();

	if (OnEndZeroGravity.IsBound())
		OnEndZeroGravity.Broadcast();
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

