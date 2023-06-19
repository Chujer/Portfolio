#include "Weapon/CHitDataAsset.h"

#include "Utilities/CLog.h"

void UCHitDataAsset::PlayHitMontage(ACharacter* InCharacter, EDamageType InDamageType)
{
	if(!!HitDatas)
		HitDatas[(int32)InDamageType].PlayHitMontage(InCharacter);
}
