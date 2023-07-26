#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill_Nomal.h"
#include "CSkill_Nomal_UpperSkill.generated.h"

UCLASS()
class UCPOTFOLIO_API UCSkill_Nomal_UpperSkill : public UCSkill_Nomal
{
	GENERATED_BODY()

public:
	UCSkill_Nomal_UpperSkill();

public:
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther) override;

private:
	UPROPERTY(EditAnywhere)
		float UpLaunchScale = 1000.0f;

	FVector LaunchVector;
};
