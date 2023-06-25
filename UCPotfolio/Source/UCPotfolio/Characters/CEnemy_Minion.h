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
	virtual void End_Hitted();
	virtual void End_Dead();

public:
	virtual void Tick(float DeltaSeconds) override;



private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* StatusComponent;

	//Todo ���� �̵� ������Ʈ ������ ���� �׷����� ��Ʈ�� �̵� �Ұ��� �ϵ���
};
