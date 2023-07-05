#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill_HaveAction.h"
#include "CHaveAction_GhostSlash.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API UCHaveAction_GhostSlash : public UCSkill_HaveAction
{
	GENERATED_BODY()

public:
	virtual void Pressed() override;

public:
	virtual void End_Skill_Implementation() override;

public:
	virtual void SkillAction1() override;
	virtual void SkillAction2() override;

	virtual void EndSkillAction1() override;


public:
	UFUNCTION()
		virtual void OnAttachmentEndCollision() override;

	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther) override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACGhostTrail> GhostTrail;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACGhostTrail> StopGhostClass;

	TArray<class ACGhostTrail*> GhostTrails;

private:
	TArray<class ACharacter*> Hitted;
};
