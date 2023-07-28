#pragma once

#include "CoreMinimal.h"
#include "CStateComponent.h"
#include "Components/ActorComponent.h"
#include "Weapon/CWeaponAsset.h"
#include "GameFramework/Character.h"
#include "CWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword, Spear, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, inNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPOTFOLIO_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DataAsset")
		class UCWeaponAsset* DataAssets[(int32)EWeaponType::Max];

public:
	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }
public:	
	UCWeaponComponent();

public:
	UFUNCTION()
		void OnStartAirCombo();
	UFUNCTION()
		void OnEndAirCombo();

public:
	class UCDoAction* GetDoAction();
	class ACAttachment* GetAttachment();
	class UCSkill* GetCurrentSkill();
public:
	void SetUnarmedMode();
	void SetSwordMode();
	void SetSpearMode();

	void DoAction();

	void DoSkillF();
	void DoSkillE();
	void DoSkillV();
	void DoSkillR();
	void DoSkillQ();
	void Released();

public:
	void Cansle();
public:
	void SetMode(EWeaponType InType);
	void ChangeType(EWeaponType InType);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FWeaponTypeChanged OnWeaponTypeChange;
private:
	TWeakObjectPtr<class ACharacter> OwnerCharacter;
	EWeaponType Type = EWeaponType::Max;
	class UCStateComponent* StateComponent;
	class UCGravityComponent* GravityComponent;
};
