#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill_HaveAction.h"
#include "Skill/AddOns/CAreaDamage_FlashSkill.h"
#include "Skill/AddOns/CSlowArea.h"
#include "CHaveAction_SwordFlashSlash.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API UCHaveAction_SwordFlashSlash : public UCSkill_HaveAction
{
	GENERATED_BODY()

public:
	virtual void Begin_Skill_Implementation() override;

public:
	virtual void Pressed() override;
	virtual void Released() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void SkillAction1() override;
	virtual void EndSkillAction1() override;

private:
	UPROPERTY(EditAnywhere, Category = "NextMontage")
		class UAnimMontage* LeadMontage;

	UPROPERTY(EditAnywhere, Category = "SlowArea")
		TSubclassOf<ACSlowArea> SlowArealClass;

	UPROPERTY(EditAnywhere, Category = "SlowArea")
		TSubclassOf<ACAreaDamage> AttackCollisionClass;

	UPROPERTY(EditAnywhere, Category = "ChargeTime")
		float MaxChargeTime = 2.0f;

private:
	TWeakObjectPtr<ACSlowArea> SlowArea;
	ACAreaDamage_FlashSkill* AttackCollision;

private:
	bool IsChargeEnd = false;
	float ChargeTime = 0.0f;

};
