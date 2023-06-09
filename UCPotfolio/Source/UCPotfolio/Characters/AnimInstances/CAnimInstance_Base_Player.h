#pragma once

#include "CoreMinimal.h"
#include "Characters/AnimInstances/CAnimInstance_Base.h"
#include "Components/CWeaponComponent.h"
#include "CAnimInstance_Base_Player.generated.h"

UCLASS()
class UCPOTFOLIO_API UCAnimInstance_Base_Player : public UCAnimInstance_Base
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUninitializeAnimation() override;

private:
	UFUNCTION()
		void OnWeaponTypeChanged(EWeaponType InPreType, EWeaponType InNewType);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		EWeaponType WeaponType = EWeaponType::Max;

private:
	class UCWeaponComponent* Weapon;
};
