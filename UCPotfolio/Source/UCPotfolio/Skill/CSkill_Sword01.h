#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill.h"
#include "CSkill_Sword01.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API UCSkill_Sword01 : public UCSkill
{
	GENERATED_BODY()

public:
	virtual void OnAttachmentEndCollision() override;

	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther) override;

public:
	virtual void End_Skill_Implementation() override;
public:
	virtual void Pressed() override;
	virtual void Released() override;



private:
	TArray<class ACharacter*> Hitted;
};
