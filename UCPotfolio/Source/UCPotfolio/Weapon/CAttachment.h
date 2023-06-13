#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeaponStructures.h"
#include "CAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipBeginAnimPlay);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipBegin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnEquipBegin);


UCLASS()
class UCPOTFOLIO_API ACAttachment : public AActor
{
	GENERATED_BODY()


public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginUnEquip();

protected:
	UFUNCTION()
		void PlayEquipAnim();

public:
	UPROPERTY(EditAnywhere)
		FEquipData EquipData;

protected:
	UFUNCTION(BlueprintCallable, Category = "Attach")
		void AttachTo(FName InSocketName);

	UFUNCTION(BlueprintCallable, Category = "Attach")
		void AttachToCollision(FName InSocketName);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USceneComponent* Root;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

public:
	FEquipBeginAnimPlay OnEquipAnimPlay;
	FEquipBegin OnEquip;
	FUnEquipBegin OnUnEquip;

protected:
	TArray<class UShapeComponent*> Collision;
};
