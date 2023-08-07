#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CWeaponComponent.h"
#include "CIdentityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetWeaponType, EWeaponType, InType);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPOTFOLIO_API UCIdentityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCIdentityComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void OnSetWeapon(EWeaponType InType);

	UFUNCTION()
		void DoIdentity();
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnSetWeaponType OnSetWeaponType;

private:
	class ACharacter* OwnerCharacter;
	EWeaponType Type = EWeaponType::Max;
	class UCWeaponComponent* WeaponComponent;
	class UCParkourComponent* ParkourComponent;
};
