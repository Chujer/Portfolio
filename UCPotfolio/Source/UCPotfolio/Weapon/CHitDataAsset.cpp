#include "Weapon/CHitDataAsset.h"

#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCHitDataAsset::PlayHitMontage(ACharacter* InCharacter, EDamageType InDamageType)
{
	if(InCharacter->GetCharacterMovement()->IsFalling())
	{
		if (!!IPKnockDownMontage)
			InCharacter->PlayAnimMontage(IPKnockDownMontage);
	}
	else
	{
		if (!!HitDatas)
			HitDatas[(int32)InDamageType].PlayHitMontage(InCharacter);
	}
}

void UCHitDataAsset::PlayHitEffect(ACharacter* InCharacter, EDamageType InDamageType)
{
	CheckNull(HitDatas);
	FHitData data = HitDatas[(int32)InDamageType];
	FTransform transform;
	transform.SetLocation(data.EffectLocation);
	transform.SetScale3D(HitDatas->EffectScale);

	CHelpers::PlayEffect(InCharacter->GetWorld(), data.Effect, transform, InCharacter->GetMesh(),data.SocketName);
}
