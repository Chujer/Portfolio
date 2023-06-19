#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CWeaponStructures.h"
#include "CHitDataAsset.generated.h"

UCLASS()
class UCPOTFOLIO_API UCHitDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	void PlayHitMontage(ACharacter* InCharacter, EDamageType InDamageType);

private:
	UPROPERTY(EditAnywhere)
		FHitData HitDatas[(int32)EDamageType::MAX];
};
