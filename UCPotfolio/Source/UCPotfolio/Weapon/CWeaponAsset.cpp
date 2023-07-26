#include "Weapon/CWeaponAsset.h"

#include "CAttachment.h"
#include "CDoAction.h"
#include "GameFramework/Character.h"

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
		DoAction = NewObject<UCDoAction>(this, DoActionClass);
		NormalDoAction = DoAction;
		DoAction->BeginPlay(InOwner, DoActionDatas);
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
		AirDoAction = NewObject<UCDoAction>(this, DoAirActionClass);
		AirDoAction->BeginPlay(InOwner, DoActionDatas);
	}
}

void UCWeaponAsset::SwapDoAction()
{
	if (DoAction == AirDoAction)
		DoAction = NormalDoAction;

	if (DoAction == NormalDoAction)
		DoAction = AirDoAction;
	
}
