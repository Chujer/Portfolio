#pragma once

#include "CoreMinimal.h"
#include "Weapon/DoAction/CDoAction_Combo.h"
#include "Combo_AirCombo.generated.h"

UCLASS()
class UCPOTFOLIO_API UCombo_AirCombo : public UCDoAction_Combo
{
	GENERATED_BODY()

public:
	virtual void DoAction() override;
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther) override;
};
