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
	virtual void Tick(float DeltaSeconds) {}

public:
	void PlayMontage();

public:
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther){};
	virtual void OnAttachmentEndCollision(){}

	virtual void Pressed();
	virtual void Released();

	UFUNCTION(BlueprintNativeEvent)
		void Begin_Skill();
	virtual void Begin_Skill_Implementation() {}

	UFUNCTION(BlueprintNativeEvent)
		void End_Skill();
	virtual void End_Skill_Implementation() {}

	FORCEINLINE ACPlayer* GetPlayer() { return Character.Get(); }
	FORCEINLINE ACAttachment* GetAttachment() { return Attachment.Get(); }

public:
	virtual void Cansle() {}

protected:
	TWeakObjectPtr<class ACPlayer> Character;
	TWeakObjectPtr<class ACAttachment> Attachment;
	TWeakObjectPtr<class UCStateComponent> StateComponent;
	TWeakObjectPtr<class UCMovementComponent> MovementComponent;

protected:	//damage 어테치먼트에서 받아옴
	EDamageType* DamageType;

protected:	//skill
	UPROPERTY(EditAnywhere, Category = "SkillData")
		FSkillData SkillData;

	bool bPressed = false;	
};
