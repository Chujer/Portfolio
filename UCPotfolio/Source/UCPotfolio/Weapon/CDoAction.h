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

public:
	//무기에 콜리전은 켰을때, 끌때 사용 (CAttachment_델리게이트)
	UFUNCTION()
		virtual void OnAttachmentBeginCollision() { }

	UFUNCTION()
		virtual void OnAttachmentEndCollision() { }

	//무기에 오버렙 됐을때, 빠져나갈때 사용 (CAttachment_델리게이트)
	UFUNCTION()
		virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther) { }

	UFUNCTION()
		virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class ACharacter* InOther) { }

protected:
	bool bInAction;

	class UCMovementComponent* Movement;
	class UCStateComponent* State;

	class ACharacter* OwnerCharacter;
	TArray<FDoActionData> DoActionDatas;
};
