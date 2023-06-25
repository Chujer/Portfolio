#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeaponStructures.h"
#include "CSkill.generated.h"

UCLASS(Abstract)
class UCPOTFOLIO_API UCSkill : public UObject
{
	GENERATED_BODY()

public:
	virtual void BeginPlay(class ACPlayer* InCharacter, class ACAttachment* InAttachment);

public:
	UCSkill();

public:
	void PlayMontage();

public:
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther){};
	virtual void OnAttachmentEndCollision(){};

	virtual void Pressed();
	virtual void Released();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Skill();
	virtual void Begin_Skill_Implementation() {};

	UFUNCTION(BlueprintNativeEvent)
		void End_Skill();
	virtual void End_Skill_Implementation() {};


protected:
	class ACPlayer* Character;
	class ACAttachment* Attachment;
	class UCStateComponent* StateComponent;
	class UCMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, Category = "SkillData")
		FSkillData SkillData;

	bool bPressed = false;	
};
