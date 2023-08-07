#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndParkour.generated.h"

UCLASS()
class UCPOTFOLIO_API UCAnimNotify_EndParkour : public UAnimNotify
{
	GENERATED_BODY()

		
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
