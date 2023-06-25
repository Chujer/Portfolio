#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeaponStructures.h"
#include "Skill/CSkill.h"
#include "CAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipBeginAnimPlay);

//무기 착용, 해제
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipBegin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnEquipBegin);

//무기 콜리전 활성화, 비활성화
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentBeginCollision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttachmentEndCollision);

//무기 오버렙 판정
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, class ACharacter*, InAttacker, AActor*, InAttackCuaser, class ACharacter*, InOther);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttachmentEndOverlap, class ACharacter*, InAttacker, class ACharacter*, InOther);


UCLASS()
class UCPOTFOLIO_API ACAttachment : public AActor
{
	GENERATED_BODY()


public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetCurrentSKill(UCSkill* InSkill) { CurrentSkill = InSkill; };
	FORCEINLINE void CurrentSkillClear() { CurrentSkill = nullptr; };
	FORCEINLINE UCSkill* GetSkill(int32 Index) { return Skills[Index]; }
	FORCEINLINE UCSkill* GetCurrentSkill() { return CurrentSkill; }

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginEquip();

	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginUnEquip();

protected:
	UFUNCTION()
		void PlayEquipAnim();

public:
	UPROPERTY(EditAnywhere)
		FEquipData EquipData;

protected:
	UFUNCTION(BlueprintCallable, Category = "Attach")
		void AttachTo(FName InSocketName);

	UFUNCTION(BlueprintCallable, Category = "Attach")
		void AttachToCollision(FName InSocketName);

protected:
	UPROPERTY(EditAnywhere, Category = "Skill")
	TSubclassOf<UCSkill> SkillsClass[(int32)ESkillIndex::MAX];

	class UCSkill* Skills[(int32)ESkillIndex::MAX];
	class UCSkill* CurrentSkill;
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class USceneComponent* Root;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void OnCollisions();
	void OffCollisions();

public:
	//무기장착
	FEquipBeginAnimPlay OnEquipAnimPlay;
	FEquipBegin OnEquip;
	FUnEquipBegin OnUnEquip;

	FAttachmentBeginCollision OnAttachmentBeginCollision;
	FAttachmentEndCollision OnAttachmentEndCollision;

	FAttachmentBeginOverlap OnAttachmentBeginOverlap;
	FAttachmentEndOverlap OnAttachmentEndOverlap;

protected:
	TArray<class UShapeComponent*> Collisions;


};

