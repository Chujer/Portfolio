#include "Weapon/CHitDataAsset.h"

#include "Global.h"
#include "Characters/CCharacter_Base.h"
#include "Characters/AnimInstances/CAnimInstance_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCHitDataAsset::PlayHitMontage(ACharacter* InCharacter, EDamageType InDamageType)
{
	ACCharacter_Base* character = Cast<ACCharacter_Base>(InCharacter);



	if(character->GetCharacterMovement()->IsFalling() || character->GetIsDown() && InDamageType != EDamageType::BACK_NOCKDOWN)
	{
		if (character->GetIsDown())
		{
			UCAnimInstance_Base* anim = Cast<UCAnimInstance_Base>(character->GetMesh()->GetAnimInstance());
			CheckNull(anim);
			anim->ResetDownTime();

			if (!!HitDatas)
			{
				HitDatas[(int32)EDamageType::BACK_NOCKDOWN_IP].PlayHitMontage(character);
			}
		}
	}
	else
		if (!!HitDatas)
		{
			HitDatas[(int32)InDamageType].PlayHitMontage(character);
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
