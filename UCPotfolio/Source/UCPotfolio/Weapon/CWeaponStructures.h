#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "CWeaponStructures.generated.h"

UENUM()
enum class EDamageType : uint8
{
	NORMAL, FRONT_NOCKDOWN, BACK_NOCKDOWN, STURN, MAX
};

USTRUCT()
struct FHitData
{
	GENERATED_BODY()

public:
	void PlayHitMontage(ACharacter* InCharacter);

public:
	UPROPERTY(EditAnywhere)
		TArray<UAnimMontage*> Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere)
		FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		FVector EffectScale = FVector::OneVector;
};

USTRUCT()
struct FEquipData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bUseControlRotation = true;

public:
	void PlayAnim(ACharacter* InCharacter);
};

USTRUCT()
struct FDoActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bUseControlRotation = true;

	UPROPERTY(EditAnywhere)
		bool bFixedCamera;

public:
	UPROPERTY(EditAnywhere)
		float Power;

	UPROPERTY(EditAnywhere)
		FVector2D Launch = FVector2D(100.0f, 0);
	
	UPROPERTY(EditAnywhere)
		float StopTime;

	UPROPERTY(EditAnywhere)
		class USoundWave* Sound;
		
	UPROPERTY(EditAnywhere)
		EDamageType DamageType = EDamageType::MAX;

	UPROPERTY(EditAnywhere)
		bool bWithLaunch;

public:
	void PlayDoAction(class ACharacter* InCharacter);

	void LaunchCharacter(class ACharacter* InSelf, class ACharacter* LaunchCharacter);
};

USTRUCT()
struct FSkillData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bUseControlRotation = true;

	UPROPERTY(EditAnywhere)
		bool bFixedCamera;

public:
	UPROPERTY(EditAnywhere)
		float Power;

	UPROPERTY(EditAnywhere)
		FVector2D Launch = FVector2D(100.0f, 0);

	UPROPERTY(EditAnywhere)
		float StopTime;

	UPROPERTY(EditAnywhere)
		EDamageType DamageType = EDamageType::MAX;

public:
	void PlayDoAction(class ACharacter* InCharacter);

	void LaunchCharacter(class ACharacter* InSelf, class ACharacter* LaunchCharacter);
};

//UCLASS()
//class UCPOTFOLIO_API UCWeaponStructures : public UObject
//{
//	GENERATED_BODY()
//};
