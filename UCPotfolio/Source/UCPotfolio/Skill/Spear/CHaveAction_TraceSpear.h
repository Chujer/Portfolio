#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill_HaveAction.h"
#include "CHaveAction_TraceSpear.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API UCHaveAction_TraceSpear : public UCSkill_HaveAction
{
	GENERATED_BODY()

public:
	virtual void Pressed() override;
	virtual void BeginPlay(ACPlayer* InCharacter, ACAttachment* InAttachment) override;
	virtual void SkillAction1() override;

private:
	UPROPERTY()
		class ACTraceSpear* TraceSpear;

public:
	UPROPERTY(EditAnywhere, Category = "MakeSpear")
		 TSubclassOf<class ACTraceSpear> TraceSpearClass;


};
