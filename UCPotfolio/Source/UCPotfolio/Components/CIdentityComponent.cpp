#include "Components/CIdentityComponent.h"
#include "Characters/CCharacter_Base.h"
#include "CParkourComponent.h"
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

	ParkourComponent = CHelpers::GetComponent<UCParkourComponent>(OwnerCharacter);

	WeaponComponent = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	CheckNull(WeaponComponent)

	OnSetWeaponType.AddDynamic(this, &UCIdentityComponent::OnSetWeapon);
}

void UCIdentityComponent::DoIdentity()
{
	switch (Type)
	{
	case EWeaponType::Max:	//맨손 - 파쿠르
		ParkourComponent->DoParkour(false);
			break;
		case EWeaponType::Sword:
			CheckNull(WeaponComponent);
			CheckNull(WeaponComponent->GetIdentity());
			WeaponComponent->GetIdentity()->DoIdentityMontage();
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

