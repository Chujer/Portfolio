#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter_Base.h"
#include  "Characters/ICharacter.h"
#include "CEnemy_Minion.generated.h"

UCLASS()
class UCPOTFOLIO_API ACEnemy_Minion : public ACCharacter_Base, public IICharacter
{
	GENERATED_BODY()
public:
	ACEnemy_Minion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	virtual void ApplyDamage(ACharacter* InAttacker, AActor* InAttackCauser, EDamageType InDamageType, float Power) override;
	virtual void ApplyDamageTimer(ACharacter* InAttacker, AActor* InAttackCauser, EDamageType InNormalDamageType, EDamageType InLastDamageType, float InNormalPower, float InLastPower, float Interval, float EndTime) override;
	virtual void End_Hitted();
	virtual void End_Dead();

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
		void OnEndZeroGravity();
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;


protected:
	FTimerHandle timer;
	FTimerHandle timer2;


private:
	ACharacter* Attacker;
	AActor* AttackCauser;
	EDamageType NormalDamageType;
	EDamageType LastDamageType;
	float NormalDamagePower;
	float LastDamagePower;

	//Todo 몬스터 이동 컴포넌트 만들지 말지 그로인해 히트중 이동 불가능 하도록
};
