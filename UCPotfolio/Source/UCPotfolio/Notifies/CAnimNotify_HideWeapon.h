#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_HideWeapon.generated.h"

UCLASS()
class UCPOTFOLIO_API UCAnimNotify_HideWeapon : public UAnimNotify
{
	GENERATED_BODY()

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
