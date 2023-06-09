#include "Components/CWeaponComponent.h"

#include "Utilities/CHelpers.h"
#include "Weapon/CAttachment.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCWeaponComponent::SetUnarmedMode()
{
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::SetSwordMode()
{
	//CheckFalse(IsIdleMode);

	SetMode(EWeaponType::Sword);
}

void UCWeaponComponent::SetSpearMode()
{
	//CheckFalse(IsIdleMode);

	SetMode(EWeaponType::Spear);
}

void UCWeaponComponent::SetMode(EWeaponType InType)
{
	if(Type == InType)
	{
		SetUnarmedMode();

		return;
	}
	else if(IsUnarmedMode() == false)
	{
	}
	ChangeType(InType);
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType prevType = Type;
	Type = InType;

	if (OnWeaponTypeChange.IsBound())
		OnWeaponTypeChange.Broadcast(prevType, InType);
	
}


void UCWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

