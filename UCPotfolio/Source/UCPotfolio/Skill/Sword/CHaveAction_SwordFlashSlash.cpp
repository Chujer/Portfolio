#include "Skill/Sword/CHaveAction_SwordFlashSlash.h"

#include <string>

#include "AITypes.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Characters/CPlayer.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/DefaultPhysicsVolume.h"
#include "Skill/AddOns/CAreaDamage_FlashSkill.h"
#include "Utilities/CLog.h"
#include "Skill/AddOns/CSlowArea.h"
#include "Weapon/CAttachment.h"
#include "Weapon/CDoAction.h"
#include "NiagaraSystem.h"

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
	SlowArea = GetWorld()->SpawnActor<ACSlowArea>(SlowArealClass, Character->GetTransform(), params);

	CheckNull(AttackCollisionClass);
	AttackCollision = GetWorld()->SpawnActor<ACAreaDamage_FlashSkill>(AttackCollisionClass, Character->GetTransform(), params);

	CheckNull(ScrewEffect);
	ScrewEffect = UNiagaraFunctionLibrary::SpawnSystemAttached( ScrewEffect->GetAsset(),Character->GetMesh(),"Root",FVector(0,0,0), FRotator(0,0,0),EAttachLocation::Type::KeepRelativeOffset,false);
	//ScrewEffect->BeginPlay();


}

void UCHaveAction_SwordFlashSlash::EndSkillAction1()
{
	ChargeTime = 0;
	Super::EndSkillAction1();
	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(Character.Get());
	AttackCollision->EndChargeDestroy();

	if(!!ScrewEffect)
		ScrewEffect->SetActive(false);


	if (!!FlowerEffect)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FlowerEffect, StartTransfsorm.GetLocation(), StartTransfsorm.GetRotation().Rotator());

	weaponComponent->GetAttachment()->ClearCurrentSkill();
	weaponComponent->SetSwordMode();
}


void UCHaveAction_SwordFlashSlash::Pressed()
{
	Super::Pressed();

	PlayMontage();
	StartTransfsorm = Character->GetActorTransform();
}

void UCHaveAction_SwordFlashSlash::Released()
{
	if (SlowArea.IsValid())
		SlowArea->RemoveArea(ChargeTime > MaxChargeTime);

	if(ChargeTime > MaxChargeTime)	//차지 완료
	{
		UCMovementComponent* movementComponent = CHelpers::GetComponent<UCMovementComponent>(Character.Get());

		FVector EndPos = Character->GetActorForwardVector() * 2500 + Character->GetActorLocation();
		FRotator rotator = Character->GetActorRotation();

		Character->TeleportTo(EndPos,FRotator(0,0,0));	//캐릭터 목표지 이동

		rotator.Yaw = rotator.Yaw + 180 - 360;

		movementComponent->SetUseControllYaw(false);
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;

		Character->GetController()->SetControlRotation(rotator);
		Character->SetActorRotation(FRotator(0, rotator.Yaw, 0));

		Character->PlayAnimMontage(LeadMontage);

		Super::Released();
		ChargeTime = 0;

		
		return;
	}

	//차지 실패
	ChargeTime = 0;
	Character->StopAnimMontage(Character->GetCurrentMontage());
	
	UCWeaponComponent* weaponComponent = CHelpers::GetComponent<UCWeaponComponent>(Character.Get());
	AttackCollision->Destroy();
	weaponComponent->GetAttachment()->ClearCurrentSkill();
	weaponComponent->GetDoAction()->End_DoAction();
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

	CheckNull(AttackCollision);
	AttackCollision->Tick(DeltaSeconds);
}
