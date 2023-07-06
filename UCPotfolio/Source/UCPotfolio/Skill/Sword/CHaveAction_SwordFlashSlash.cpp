#include "Skill/Sword/CHaveAction_SwordFlashSlash.h"

#include <string>

#include "Global.h"
#include "Characters/ICharacter.h"
#include "Characters/CPlayer.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"
#include "Utilities/CLog.h"

void UCHaveAction_SwordFlashSlash::Begin_Skill_Implementation()
{
	Super::Begin_Skill_Implementation();
}

void UCHaveAction_SwordFlashSlash::SkillAction1()
{
	Super::SkillAction1();


}

void UCHaveAction_SwordFlashSlash::Pressed()
{
	Super::Pressed();
	//CLog::Print("SwordFlashSlash : Pressed : " + IsChargeEnd,1);
	PlayMontage();
}

void UCHaveAction_SwordFlashSlash::Released()
{
	if(ChargeTime > MaxChargeTime)
	{
		UCMovementComponent* movementComponent = CHelpers::GetComponent<UCMovementComponent>(Character.Get());

		FRotator rotator = Character->GetActorRotation();
		rotator.Yaw = rotator.Yaw - 180;

		CLog::Print(Character->GetActorRotation(), 4,10, FColor::Blue);
		movementComponent->SetUseControllYaw(false);
		Character->SetActorRotation(rotator);
		CLog::Print(Character->GetActorRotation(), 5,10, FColor::Blue);


		Character->PlayAnimMontage(LeadMontage);
	}
	ChargeTime = 0;
	//IsChargeEnd = false;
	CLog::Print("SwordFlashSlash : Released : " ,2);


	Super::Released();
}

void UCHaveAction_SwordFlashSlash::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Tick은 CurrentSkill만 사용하지만 Released에 들어가면 실행하지 않음
	ChargeTime += DeltaSeconds;

	if (ChargeTime > MaxChargeTime)
	{
		CLog::Print("SwordFlashSlash : Tick :  EndCharge",3);
	}

}
