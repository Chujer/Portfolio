#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon/CWeaponStructures.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

class UCPOTFOLIO_API IICharacter
{
	GENERATED_BODY()

public:
	virtual void ApplyDamage(ACharacter* InAttacker, AActor* InAttackCauser, EDamageType InDamageType, float Power) {};
	virtual void End_Hitted() { };
	virtual void End_Dead() = 0;

public:
	void Change_Color(class ACharacter* InCharacter, FLinearColor InColor);
};
