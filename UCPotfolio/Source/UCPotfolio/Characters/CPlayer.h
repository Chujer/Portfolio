#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter_Base.h"
#include "Components/CStateComponent.h"
#include "CPlayer.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API ACPlayer : public ACCharacter_Base
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCMovementComponent* Movement;

	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCRollComponent* RollComponent;
};
