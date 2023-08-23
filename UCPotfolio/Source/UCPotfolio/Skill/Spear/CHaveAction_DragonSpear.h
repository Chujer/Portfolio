#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill_HaveAction.h"
#include "CHaveAction_DragonSpear.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API UCHaveAction_DragonSpear : public UCSkill_HaveAction
{
	GENERATED_BODY()

public:
	virtual void Pressed() override;
	virtual void SkillAction1() override;
	virtual void SkillAction2() override;
	virtual void SkillAction3() override;
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACSpeare_Pull> PullAddOnClass;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* SmokeNiagara;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* AttackEndNiagara;

		


	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> DragonActor;

	UPROPERTY(EditAnywhere)
		UAnimMontage* FinishMontage;

	UPROPERTY(EditAnywhere, Category = "AttackAttribute")
		float Power;

	UPROPERTY(EditAnywhere, Category = "AttackAttribute")
		EDamageType DamageType;

private:
	ACSpeare_Pull* PullAddOn;
	class UNiagaraComponent* Smoke;
};
