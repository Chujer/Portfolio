#include "Weapon/CWeaponAsset.h"

#include "CAttachment.h"
#include "CDoAction.h"
#include "GameFramework/Character.h"


void UCWeaponAsset::SetDoAirAction()
{
	if (!!Attachment)
	{
		//TODO(2023.08.10) : 기본공격중에 변경은 문제가 없으나 스킬중에는 기본공격을 지우고 스킬로 델리게이트를 변경하여 문제발생 
		Attachment->OnAttachmentBeginOverlap.RemoveDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);
		DoAction = DoAirAction;
		Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);
	}
}

void UCWeaponAsset::SetDoNormalAction()
{ 
	if (!!Attachment)
	{
		Attachment->OnAttachmentBeginOverlap.RemoveDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);
		DoAction = DoNormalAction;
		Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);
	}
}

UCWeaponAsset::UCWeaponAsset()
{
	AttachmentClass = ACAttachment::StaticClass();
}

void UCWeaponAsset::BeginPlay(ACharacter* InOwner)
{
	if(!!AttachmentClass)
	{
		FActorSpawnParameters param;
		param.Owner = InOwner;

		Attachment = InOwner->GetWorld()->SpawnActor<ACAttachment>(AttachmentClass, param);

	}

	if(!!DoActionClass)
	{
		DoNormalAction = NewObject<UCDoAction>(this, DoActionClass);
		DoNormalAction->BeginPlay(InOwner, DoActionDatas);
		DoAction = DoNormalAction;
		if (!!Attachment)
		{
			Attachment->OnAttachmentBeginCollision.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginCollision);
			Attachment->OnAttachmentEndCollision.AddDynamic(DoAction, &UCDoAction::OnAttachmentEndCollision);
			
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentEndOverlap);
		}

	}

	if (!!DoAirActionClass)
	{
		DoAirAction = NewObject<UCDoAction>(this, DoAirActionClass);
		DoAirAction->BeginPlay(InOwner, DoAirActionDatas);
		Attachment->OnAttachmentEndCollision.AddDynamic(DoAirAction, &UCDoAction::OnAttachmentEndCollision);
	}
}
