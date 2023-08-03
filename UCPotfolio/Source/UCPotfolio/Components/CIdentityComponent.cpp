#include "Components/CIdentityComponent.h"
#include "Characters/CCharacter_Base.h"
#include "Global.h"

UCIdentityComponent::UCIdentityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCIdentityComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	CheckNull(WeaponComponent)

	OnSetWeaponType.AddDynamic(this, &UCIdentityComponent::OnSetWeapon);
}

void UCIdentityComponent::DoIdentity()
{
	switch (Type)
	{
	case EWeaponType::Max:
		CLog::Log("Unarmde");
			//맨손 - 파쿠르
			break;
		case EWeaponType::Sword:
		CLog::Log("SwordMode");
			//검 - 대쉬
			break;
		case EWeaponType::Spear:
		CLog::Log("SpearMode");
			//창 - 반격기
			break;
	}
}

void UCIdentityComponent::OnSetWeapon(EWeaponType InType)
{
	Type = InType;
}

void UCIdentityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

