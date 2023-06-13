#pragma once

#include "CoreMinimal.h"
#include "CWeaponStructures.h"
#include "Weapon/CWeaponStructures.h"
#include "CDoAction.generated.h"


UCLASS(Abstract, NotBlueprintable)
class UCPOTFOLIO_API UCDoAction : public UObject
{
	GENERATED_BODY()

public:
	UCDoAction();

public:
	virtual void BeginPlay(class ACharacter* InOwner, const TArray<FDoActionData>& InDoActionDatas);

public:
	virtual void DoAction();
	virtual	void Begin_DoAction();
	virtual void End_DoAction();

protected:
	bool bInAction;

	class UCMovementComponent* Movement;
	class UCStateComponent* State;

	class ACharacter* OwnerCharacter;
	TArray<FDoActionData> DoActionDatas;
};
