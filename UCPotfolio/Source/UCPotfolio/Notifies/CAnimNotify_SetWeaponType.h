#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Components/CWeaponComponent.h"
#include "CAnimNotify_SetWeaponType.generated.h"

UCLASS()
class UCPOTFOLIO_API UCAnimNotify_SetWeaponType : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere)
		EWeaponType WeaponType;
};
