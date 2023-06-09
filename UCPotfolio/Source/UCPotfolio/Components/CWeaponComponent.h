#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword, Spear, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, inNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPOTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCWeaponComponent();

public:
	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }

public:
	void SetUnarmedMode();
	void SetSwordMode();
	void SetSpearMode();

public:
	void SetMode(EWeaponType InType);
	void ChangeType(EWeaponType InType);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FWeaponTypeChanged OnWeaponTypeChange;

private:
	class ACharacter* OwnerCharacter;
	EWeaponType Type = EWeaponType::Max;

public:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
		TSubclassOf<class ACAttachment> DataAssets[(int32)EWeaponType::Max];
};
