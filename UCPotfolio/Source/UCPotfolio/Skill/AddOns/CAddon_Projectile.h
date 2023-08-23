#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapon/CAttachment.h"
#include "Skill/CHaveAction_CreateProjectile.h"
#include "CAddon_Projectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeginOverlapEnemy, ACharacter*, InOtherCharacter, EDamageType, InDamageType);

UCLASS()
class UCPOTFOLIO_API ACAddon_Projectile : public AActor
{
	GENERATED_BODY()

public:
	ACAddon_Projectile();

public:
	FORCEINLINE void AddIgnoreActor(AActor* InActor) { Ignores.Add(InActor); }

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		 virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


private:
	UPROPERTY(EditAnywhere, Category = "DamageType")
		EDamageType DamageType;

	UPROPERTY(EditAnywhere, Category = "LifeTime")
		float LifeSpawnAfterCollision = 1.0f;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileComponent;
private:
	TArray<AActor*> Ignores;

public:
	FOnBeginOverlapEnemy OnBeginOverlapEnemy;

};