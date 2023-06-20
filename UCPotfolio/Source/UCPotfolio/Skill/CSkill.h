#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSkill.generated.h"

UCLASS()
class UCPOTFOLIO_API UCSkill : public UObject
{
	GENERATED_BODY()

public:
	virtual void Play() {};

private:
	UPROPERTY(EditAnywhere)
		UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
		float Power;
		
};
