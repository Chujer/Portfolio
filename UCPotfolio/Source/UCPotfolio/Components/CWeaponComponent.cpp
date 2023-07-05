#include "Components/CWeaponComponent.h"

#include "Skill/CSkill.h"
#include "Utilities/CHelpers.h"
#include "Weapon/CAttachment.h"
#include "Weapon/CDoAction.h"
#include "Weapon/CWeaponAsset.h"
#include "GameFramework/Character.h"

UCWeaponComponent::UCWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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

UCSkill* UCWeaponComponent::GetCurrentSkill()
{
	return GetAttachment()->GetCurrentSkill();
}


void UCWeaponComponent::SetUnarmedMode()
{
	ChangeType(EWeaponType::Max);
}

void UCWeaponComponent::SetSwordMode()
{
	//CheckFalse(IsIdleMode);

	SetMode(EWeaponType::Sword);
}

void UCWeaponComponent::SetSpearMode()
{
	//CheckFalse(IsIdleMode);

	SetMode(EWeaponType::Spear);
}

void UCWeaponComponent::DoAction()
{
	if(!!GetDoAction())
		GetDoAction()->DoAction();
}

void UCWeaponComponent::DoSkillF()
{
	CheckNull(GetAttachment());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::F));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();		
}

void UCWeaponComponent::DoSkillE()
{
	CheckNull(GetAttachment());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::E));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::DoSkillV()
{
	CheckNull(GetAttachment());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::V));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::DoSkillR()
{
	CheckNull(GetAttachment());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::R));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::DoSkillQ()
{
	CheckNull(GetAttachment());
	GetAttachment()->SetCurrentSKill(GetAttachment()->GetSkill((int32)ESkillIndex::Q));	//현재 스킬 설정
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Pressed();
}

void UCWeaponComponent::Released()
{
	CheckNull(GetAttachment());
	CheckNull(GetCurrentSkill());
	GetCurrentSkill()->Released();
}


void UCWeaponComponent::SetMode(EWeaponType InType)
{
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
		ChangeType(InType);

		if (prevAttachment->OnUnEquip.IsBound())
			prevAttachment->OnUnEquip.Broadcast();

		if (newAttachment->OnEquip.IsBound())
			newAttachment->OnEquip.Broadcast();
	}
}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
	EWeaponType prevType = Type;
	Type = InType;

	if (OnWeaponTypeChange.IsBound())
		OnWeaponTypeChange.Broadcast(prevType, InType);
	
}


void UCWeaponComponent::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	for(UCWeaponAsset* Asset : DataAssets)
	{
		if (!!Asset)
			Asset->BeginPlay(OwnerCharacter.Get());
	}

	Super::BeginPlay();
}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

