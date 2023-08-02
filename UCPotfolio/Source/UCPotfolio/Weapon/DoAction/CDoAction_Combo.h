#pragma once

#include "CoreMinimal.h"
#include "Weapon/CDoAction.h"
#include "CDoAction_Combo.generated.h"

UCLASS()
class UCPOTFOLIO_API UCDoAction_Combo : public UCDoAction
{
	GENERATED_BODY()

public:
	UCDoAction_Combo();

public:
	FORCEINLINE void EnableCombo() { bEnable = true; }
	FORCEINLINE bool GetEnableCombo() { return bEnable; }
	FORCEINLINE void DisableCombo() { bEnable = false; }

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

public:
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther) override;
	virtual void OnAttachmentEndCollision() override;
protected:
	int32 Index;

	bool bEnable;
	bool bExist;
	bool bHitStop = false;
protected:
	TArray<class ACharacter*> Hitted;
};
