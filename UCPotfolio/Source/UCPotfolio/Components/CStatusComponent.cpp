#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"
#include "Global.h"

UCStatusComponent::UCStatusComponent()
{
}


void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	Health = MaxHealth;


}

void UCStatusComponent::Damage(float InAmount)
{
	Health += (InAmount * -1.0f);
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

