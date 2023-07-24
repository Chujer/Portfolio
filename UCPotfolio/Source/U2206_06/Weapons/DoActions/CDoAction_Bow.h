#pragma once

#include "CoreMinimal.h"
#include "Weapons/CDoAction.h"
#include "CDoAction_Bow.generated.h"

UCLASS()
class U2206_06_API UCDoAction_Bow : public UCDoAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Arrow")
		TSubclassOf<class ACProjectile> ArrowClass;

public:
	FORCEINLINE void AttachString() { bAttachedString = true; }

public:
	UCDoAction_Bow();

	virtual void BeginPlay
	(
		class ACAttachment* InAttachment,
		class UCEquipment* InEquipment,
		class ACharacter* InOwner,
		const TArray<FDoActionData>& InDoActionData,
		const TArray<FHitData>& InHitData
	) override;

	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void Tick(float InDeltaTime) override;

	virtual void OnEquip() override;
	virtual void OnBeginEquip() override;
	virtual void OnEndEquip() override;
	virtual void OnBeginUnEquip() override;

private:
	void CreateArrow();
	class ACProjectile* GetAttachedArrow();

private:
	UFUNCTION()
		void OnArrowHit(class AActor* InCauser, class ACharacter* InOtherCharacter);

	UFUNCTION()
		void OnArrowEndPlay(class ACProjectile* InDestroyer);

private:
	class USkeletalMeshComponent* SkeletalMesh;
	class UPoseableMeshComponent* PoseableMesh;

private:
	TArray<class ACProjectile*> Arrows;
	FVector OriginLocation;

	bool bEndEquip;	//활줄 이을 시점
	bool bAttachedString = true;

private:
	float* Bending;
};
