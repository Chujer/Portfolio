#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill.h"
#include "CSkill_Nomal.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API UCSkill_Nomal : public UCSkill
{
	GENERATED_BODY()

public:
	virtual void BeginPlay(ACPlayer* InCharacter, ACAttachment* InAttachment) override;
	UFUNCTION()
		virtual void OnAttachmentEndCollision() override;

	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther) override;

public:
	virtual void End_Skill_Implementation() override;
public:
	virtual void Pressed() override;
	virtual void Released() override;
	virtual void Cansle() override;


protected:
	TArray<class ACharacter*> Hitted;
};
