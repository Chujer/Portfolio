#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill_HaveAction.h"
#include "CHaveAction_SwordFlashSlash.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API UCHaveAction_SwordFlashSlash : public UCSkill_HaveAction
{
	GENERATED_BODY()

public:
	virtual void Begin_Skill_Implementation() override;

public:
	virtual void SkillAction1() override;
	virtual void Pressed() override;
	virtual void Released() override;

	virtual void Tick(float DeltaSeconds) override;


private:
	UPROPERTY(EditAnywhere, Category = "NextMontage")
		class UAnimMontage* LeadMontage;
private:
	//bool IsChargeEnd = false;
	float MaxChargeTime = 2.0f;
	float ChargeTime = 0.0f;
};
