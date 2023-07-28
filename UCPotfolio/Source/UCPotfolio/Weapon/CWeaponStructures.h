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

	UPROPERTY(EditAnywhere, Category = "Effect")
		class UFXSystemAsset* Effect;

	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector EffectLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Effect")
		FVector EffectScale = FVector::OneVector;

	UPROPERTY(EditAnywhere, Category = "Effect")
		FName SocketName = FName("");
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
		FVector Launch = FVector(100.0f, 0,0);
	
	UPROPERTY(EditAnywhere)
		float StopTime;

	UPROPERTY(EditAnywhere)
		class USoundWave* Sound;

	UPROPERTY(EditAnywhere)
		bool bWithLaunch = false;

public:
	void PlayDoAction(class ACharacter* InCharacter);

	void LaunchCharacter(class ACharacter* InSelf, class ACharacter* LaunchCharacter);
};

UENUM()
enum class ESkillIndex : uint8
{
	F= 0, E, V, R, Q, MAX
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
		bool bFixedCamera;

	UPROPERTY(EditAnywhere)
		float Power;

	UPROPERTY(EditAnywhere)
		FVector Launch = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		float StopTime;
};


//UCLASS()
//class UCPOTFOLIO_API UCWeaponStructures : public UObject
//{
//	GENERATED_BODY()
//};
