#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndDoAction.generated.h"

UCLASS()
class UCPOTFOLIO_API UCAnimNotify_EndDoAction : public UAnimNotify
{
	GENERATED_BODY()

private:
	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
