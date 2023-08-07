#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter_Base.h"
#include "Components/CParkourComponent.h"
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
	void OnActorHitted(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	virtual void Landed(const FHitResult& Hit) override;

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	void CreateArrow();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCRollComponent* RollComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCIdentityComponent* IdentityComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCParkourComponent* ParkourComponent;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* ArrowGroup;
	UPROPERTY(VisibleDefaultsOnly)
		TArray<class UArrowComponent*> Arrows;

};
