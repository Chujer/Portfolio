#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill_HaveAction.h"
#include "CHaveAction_CreateProjectile.generated.h"


class ACAddon_Projectile;
UCLASS(Blueprintable)
class UCPOTFOLIO_API UCHaveAction_CreateProjectile : public UCSkill_HaveAction
{
	GENERATED_BODY()

public:
	virtual void Pressed() override;

	virtual void SkillAction1() override;

	UFUNCTION()
		virtual void BeginOverlap(ACharacter* InOtherCharacter, EDamageType InDamageType);

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACAddon_Projectile> ProjectileClass;

protected:
	class ACAddon_Projectile* ProjectilActor;

};
