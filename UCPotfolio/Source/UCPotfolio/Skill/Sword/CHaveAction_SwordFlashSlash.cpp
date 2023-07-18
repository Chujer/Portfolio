#include "Skill/Sword/CHaveAction_SwordFlashSlash.h"

#include <string>

#include "Global.h"
#include "Characters/ICharacter.h"
#include "Characters/CPlayer.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"
#include "Utilities/CLog.h"
#include "Skill/AddOns/CSlowArea.h"
#include "Weapon/CAttachment.h"
#include "Weapon/CDoAction.h"

void UCHaveAction_SwordFlashSlash::Begin_Skill_Implementation()
{
	Super::Begin_Skill_Implementation();
}

void UCHaveAction_SwordFlashSlash::SkillAction1()
{
	Super::SkillAction1();

	FVector vector = Character->GetActorLocation();

	FActorSpawnParameters params;
	params.Owner = Character.Get();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform transform;
	transform.SetTranslation(vector);

	CheckNull(SlowArealClass);
	SlowArea = GetWorld()->SpawnActor<ACSlowArea>(SlowArealClass, transform, params);

	CheckNull(SlowArea);
	SlowArea->BeginPlay(Cast<ACharacter>(Character));
}

void UCHaveAction_SwordFlashSlash::EndSkillAction1()
{
	ChargeTime = 0;
	Super::EndSkillAction1();
	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(Character.Get());
	
	weaponComponent->GetAttachment()->ClearCurrentSkill();
	weaponComponent->SetSwordMode();

}


void UCHaveAction_SwordFlashSlash::Pressed()
{
	Super::Pressed();

	PlayMontage();
}

void UCHaveAction_SwordFlashSlash::Released()
{
	if (SlowArea.IsValid())
		SlowArea->RemoveArea(ChargeTime > MaxChargeTime);
	if(ChargeTime > MaxChargeTime)
	{
		UCMovementComponent* movementComponent = CHelpers::GetComponent<UCMovementComponent>(Character.Get());

		FRotator rotator = Character->GetActorRotation();
		rotator.Yaw = rotator.Yaw - 180;

		movementComponent->SetUseControllYaw(false);
		Character->SetActorRotation(rotator);


		Character->PlayAnimMontage(LeadMontage);
		Super::Released();
		ChargeTime = 0;
		return;
	}

	ChargeTime = 0;
	Character->StopAnimMontage(Character->GetCurrentMontage());
	CHelpers::GetComponent<UCWeaponComponent>(Character.Get())->GetDoAction()->End_DoAction();
	//IsChargeEnd = false;
	//CLog::Print("SwordFlashSlash : Released : " ,2);


	Super::Released();
}

void UCHaveAction_SwordFlashSlash::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ChargeTime += DeltaSeconds;

	if (ChargeTime > MaxChargeTime)
	{
	}

	CheckNull(SlowArea);
	SlowArea->Tick(DeltaSeconds);
}
