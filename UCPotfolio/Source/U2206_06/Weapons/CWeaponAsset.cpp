#include "Weapons/CWeaponAsset.h"
#include "Global.h"
#include "CAttachment.h"
#include "CEquipment.h"
#include "CDoAction.h"
#include "CSubAction.h"
#include "CWeaponData.h"
#include "GameFramework/Character.h"

UCWeaponAsset::UCWeaponAsset()
{
	AttachmentClass = ACAttachment::StaticClass();
	EquipmentClass = UCEquipment::StaticClass();
	//SubActionClass = UCSubAction::StaticClass();
}

void UCWeaponAsset::BeginPlay(ACharacter * InOwner, UCWeaponData** OutWeaponData)
{
	ACAttachment* Attachment = nullptr;

	if (!!AttachmentClass)
	{
		FActorSpawnParameters params;
		params.Owner = InOwner;

		Attachment = InOwner->GetWorld()->SpawnActor<ACAttachment>(AttachmentClass, params);
	}

	UCEquipment* Equipment = nullptr;

	if (!!EquipmentClass)
	{
		Equipment = NewObject<UCEquipment>(this, EquipmentClass);
		Equipment->BeginPlay(InOwner, EquipmentData);

		if (!!Attachment)
		{
			Equipment->OnEquipmentBeginEquip.AddDynamic(Attachment, &ACAttachment::OnBeginEquip);
			Equipment->OnEquipmentUnequip.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
		}
	}

	UCDoAction* DoAction = nullptr;

	if (!!DoActionClass)
	{
		DoAction = NewObject<UCDoAction>(this, DoActionClass);
		DoAction->BeginPlay(Attachment, Equipment, InOwner, DoActionDatas, HitDatas);

		if (!!Attachment)
		{
			Attachment->OnAttachmentBeginCollision.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginCollision);
			Attachment->OnAttachmentEndCollision.AddDynamic(DoAction, &UCDoAction::OnAttachmentEndCollision);

			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentEndOverlap);
		}

		if(!!Equipment)
		{
			Equipment->OnEquipmentEquip.AddDynamic(DoAction, &UCDoAction::UCDoAction::OnEquip);
			Equipment->OnEquipmentBeginEquip.AddDynamic(DoAction, &UCDoAction::OnBeginEquip);
			Equipment->OnEquipmentEndEquip.AddDynamic(DoAction, &UCDoAction::OnEndEquip);
			Equipment->OnEquipmentUnequip.AddDynamic(DoAction, &UCDoAction::OnBeginUnEquip);
		}
	}

	UCSubAction* SubAction = nullptr;

	if(!!SubActionClass)
	{
		SubAction = NewObject<UCSubAction>(this, SubActionClass);
		SubAction->BeginPlay(InOwner, Attachment, DoAction);
	}

	*OutWeaponData = NewObject<UCWeaponData>();
	(*OutWeaponData)->Attachment = Attachment;
	(*OutWeaponData)->Equipment = Equipment;
	(*OutWeaponData)->DoAction = DoAction;
	(*OutWeaponData)->SubAction = SubAction;	

}

#if WITH_EDITOR
void UCWeaponAsset::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	CheckTrue(FApp::IsGame());	//���ӽ��������� �Ǻ�

	bool bRefresh = false;
	bRefresh |= PropertyChangedEvent.GetPropertyName().Compare("DoActionDatas") == 0;	//�ٲ���� �����Ͱ� ����
	bRefresh |= (PropertyChangedEvent.GetPropertyName().Compare("HitDatas") == 0);
	
	if(bRefresh)
	{
		bool bCheck = false;
		bCheck |= (PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd);
		bCheck |= (PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove);
		bCheck |= (PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear);
		bCheck |= (PropertyChangedEvent.ChangeType == EPropertyChangeType::Duplicate);

		if(bCheck)
		{
			FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			TSharedPtr<IDetailsView> detailsView = prop.FindDetailView("WeaponAssetEditorDetailsView");
			
			if (detailsView.IsValid())
				detailsView->ForceRefresh();	//�簻��
		}
	}
}
#endif //WITH_EDITOR

