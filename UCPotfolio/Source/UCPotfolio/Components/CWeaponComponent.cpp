#include "Components/CWeaponComponent.h"

#include "CGravityComponent.h"
#include "CMovementComponent.h"
#include "CParkourComponent.h"
#include "Characters/CPlayer.h"
#include "Skill/CSkill.h"
#include "Utilities/CHelpers.h"
#include "Weapon/CAttachment.h"
#include "Weapon/CDoAction.h"
#include "Weapon/CWeaponAsset.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CIdentityComponent.h"
#include "Utilities/CLog.h"
#include "Identity/CIdentity.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCWeaponComponent::OnStartAirCombo()
{
	for(UCWeaponAsset* asset : DataAssets)
	{
		if (!asset->GetDoAirAction())
			break;
		if(!!asset)
		{
			if(asset->GetDoAction() != asset->GetDoAirAction())
				asset->SetDoAirAction();
		}
	}
}

void UCWeaponComponent::OnEndAirCombo()
{
	for (UCWeaponAsset* asset : DataAssets)
	{
		if (!!asset)
		{
			if (asset->GetDoAction() != asset->GetDoNormalAction())
			{
				asset->SetDoNormalAction();
			}
		}
	}
}


UCDoAction* UCWeaponComponent::GetDoAction()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(!!DataAssets[(int32)Type], nullptr);

	return DataAssets[(int32)Type]->GetDoAction();
}

ACAttachment* UCWeaponComponent::GetAttachment()
{
	CheckTrueResult(IsUnarmedMode(), nullptr);
	CheckFalseResult(!!DataAssets[(int32)Type], nullptr);

	return DataAssets[(int32)Type]->GetAttachment();
}

UCIdentity* UCWeaponComponent::GetIdentity()
{
	CheckNullResult(GetAttachment(), nullptr);
	CheckNullResult(GetAttachment()->GetIdentity(), nullptr);

	return GetAttachment()->GetIdentity();
}

UCSkill* UCWeaponComponent::GetCurrentSkill()
{
	CheckNullResult(GetAttachment(), nullptr);
	CheckNullResult(GetAttachment()->GetCurrentSkill(), nullptr);

	return GetAttachment()->GetCurrentSkill();
}


void UCWeaponComponent::SetUnarmedMode()
{
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::SetSwordMode()
{
	CheckFalse(StateComponent->IsIdleMode());

	SetMode(EWeaponType::Sword);
}

void UCWeaponComponent::SetSpearMode()
{
	CheckFalse(StateComponent->IsIdleMode());

	SetMode(EWeaponType::Spear);
}

void UCWeaponComponent::DoAction()
{
	if(CHelpers::GetComponent<UCMovementComponent>(OwnerCharacter)->IsSprint())
	{
		DoDashAttack();
	}
	else if (!!GetDoAction())
	{
		GetDoAction()->DoAction();
	}
}

void UCWeaponComponent::DoSkillF()
{
	CheckNull(GetAttachment());
	CheckFalse(StateComponent->IsIdleMode());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::F));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();		
}

void UCWeaponComponent::DoSkillE()
{
	CheckNull(GetAttachment());
	CheckFalse(StateComponent->IsIdleMode());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::E));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::DoSkillV()
{
	CheckNull(GetAttachment());
	CheckFalse(StateComponent->IsIdleMode());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::V));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::DoSkillR()
{
	CheckNull(GetAttachment());
	CheckFalse(StateComponent->IsIdleMode());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::R));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::DoSkillQ()
{
	CheckNull(GetAttachment());
	CheckFalse(StateComponent->IsIdleMode());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::Q));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::DoDashAttack()
{
	CheckNull(GetAttachment());
	CheckFalse(StateComponent->IsIdleMode());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::DashAttack));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::Released()
{
	CheckNull(GetAttachment());
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Released();
}

void UCWeaponComponent::Cansle()
{
	if (GetCurrentSkill())
		GetCurrentSkill()->Cansle();

	if (GetDoAction())
		GetDoAction()->End_DoAction();
}


void UCWeaponComponent::SetMode(EWeaponType InType)
{
	CheckTrue(ParkourComponent->IsExecuting());

	ACAttachment* prevAttachment = DataAssets[(int32)Type]->GetAttachment();
	ACAttachment* newAttachment = DataAssets[(int32)InType]->GetAttachment();

	if (Type == InType)	//무기 -> 맨손
	{
		if (prevAttachment->OnUnEquip.IsBound())
			prevAttachment->OnUnEquip.Broadcast();

		SetUnarmedMode();
	}
	else if (IsUnarmedMode() == true)	//맨손 -> 장착
	{
		if(newAttachment->OnEquipAnimPlay.IsBound())
			newAttachment->OnEquipAnimPlay.Broadcast();

		ChangeType(InType);
	}
	else //무기 -> 다른무기
	{
		if (prevAttachment->OnUnEquip.IsBound())
			prevAttachment->OnUnEquip.Broadcast();

		if (newAttachment->OnEquip.IsBound())
			newAttachment->OnEquip.Broadcast();

		ChangeType(InType);
	}

	
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType prevType = Type;
	Type = InType;


	if (OnWeaponTypeChange.IsBound())
		OnWeaponTypeChange.Broadcast(prevType, InType);

	if (IdentityComponent->OnSetWeaponType.IsBound())
		IdentityComponent->OnSetWeapon(InType);

	UCMovementComponent* movementComponent = CHelpers::GetComponent<UCMovementComponent>(OwnerCharacter.Get());
	CheckNull(movementComponent);

	if (Type == EWeaponType::Max)
	{
		movementComponent->SetUseControllYaw(false);
	}
	else
	{
		movementComponent->SetUseControllYaw(true);
	}

}


void UCWeaponComponent::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	StateComponent = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	GravityComponent = CHelpers::GetComponent<UCGravityComponent>(OwnerCharacter);
	IdentityComponent = CHelpers::GetComponent<UCIdentityComponent>(OwnerCharacter);
	ParkourComponent = CHelpers::GetComponent<UCParkourComponent>(OwnerCharacter);

	for(UCWeaponAsset* Asset : DataAssets)
	{
		if (!!Asset)
		{
			Asset->BeginPlay(OwnerCharacter.Get());
		}
	}

	CheckNull(GravityComponent);

	GravityComponent->OnStartZeroGravity.AddDynamic(this, &UCWeaponComponent::OnStartAirCombo);
	GravityComponent->OnEndZeroGravity.AddDynamic(this, &UCWeaponComponent::OnEndAirCombo);

	Super::BeginPlay();
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!!GetIdentity())
		GetIdentity()->Tick(DeltaTime);

	if (!!GetCurrentSkill())
	{
		GetCurrentSkill()->Tick(DeltaTime);
	}
	else
		CLog::Print("NullSkill", 3);
}

