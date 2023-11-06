#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/CHitDataAsset.h"
#include "CCharacter_Base.generated.h"



UCLASS(Abstract)
class UCPOTFOLIO_API ACCharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacter_Base();

protected:
	virtual void BeginPlay() override;
	void SetMesh(FString InPath);

public:
	FORCEINLINE bool GetIsDown() { return bDown; }
	FORCEINLINE void SetIsDown(bool InBool) { bDown = InBool; }


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//원본 머테리얼
	void SetOriginMaterials(USkeletalMesh* InSkeletaMesh);
	void SetMaterialToOrigin();

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		class UCGravityComponent* GravityComponent;


	UPROPERTY(VisibleAnywhere)
		TArray<FSkeletalMaterial> OriginMaterials;

	UPROPERTY(EditAnywhere)
		class UCHitDataAsset* HitDataAssets;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UCStatusComponent* StatusComponent;

protected:
	bool bDown = false;
};
