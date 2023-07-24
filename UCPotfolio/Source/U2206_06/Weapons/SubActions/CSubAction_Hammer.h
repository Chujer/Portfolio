#pragma once

#include "CoreMinimal.h"
#include "Weapons/CSubAction.h"
#include "Weapons/CWeaponStructures.h"
#include "CSubAction_Hammer.generated.h"

UCLASS(Blueprintable)
class U2206_06_API UCSubAction_Hammer : public UCSubAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Aura")
		TSubclassOf<class ACAura> AuraClass;

	UPROPERTY(EditDefaultsOnly, Category = "Aura")
		FVector AuraLocation;

private:
	UPROPERTY(EditAnywhere, Category = "Action")
		FDoActionData ActionData;

	UPROPERTY(EditDefaultsOnly, Category = "Add-On")
		TSubclassOf<class ACGhostTrail> GhostTrailClass;

public:
	void Pressed() override;

	virtual void Begin_SubAction_Implementation() override;
	virtual void End_SubAction_Implementation() override;

private:
	class ACGhostTrail* GhostTrail;
};
