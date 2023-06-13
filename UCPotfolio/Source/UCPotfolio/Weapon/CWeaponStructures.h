#pragma once

#include "CoreMinimal.h"
#include "CWeaponStructures.generated.h"

UENUM()
enum class EDamageType : uint8
{
	NORMAL, FRONT_NOCKDOWN, BACK_NOCKDOWN, STURN, MAX
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

	UPROPERTY(EditAnywhere)
		EDamageType DamageType = EDamageType::MAX;

public:
	void PlayDoAction(class ACharacter* InCharacter);
};

//UCLASS()
//class UCPOTFOLIO_API UCWeaponStructures : public UObject
//{
//	GENERATED_BODY()
//};
