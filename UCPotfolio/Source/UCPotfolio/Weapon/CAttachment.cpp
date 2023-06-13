#include "Weapon/CAttachment.h"
#include "Global.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"
#include "Utilities/CLog.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateComponent(this, &Root, "Root");
}

void ACAttachment::BeginPlay()
{

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	//���� �ݸ��� ���
	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);	//bincludeAllDescendants : �ڳ� ��Ͽ� ��� �ڼ��� �������� ���Ѵ�.
	for(USceneComponent* child : children)
	{
		UShapeComponent* shape = Cast<UShapeComponent>(child);

		if(!!shape)
		{
			Collision.Add(shape);
		}
	}

	OnEquipAnimPlay.AddDynamic(this, &ACAttachment::PlayEquipAnim);
	OnEquip.AddDynamic(this, &ACAttachment::OnBeginEquip);
	OnUnEquip.AddDynamic(this, &ACAttachment::OnBeginUnEquip);

	Super::BeginPlay();
}

void ACAttachment::PlayEquipAnim()
{
	if (!!OwnerCharacter && !!EquipData.Montage)
		EquipData.PlayAnim(OwnerCharacter);
	else
		OnBeginEquip();
}

void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::AttachToCollision(FName InSocketName)
{
	for(UShapeComponent* collision : Collision)
	{
		if(collision->GetName() == InSocketName.ToString())
		{
			collision->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
			return;
		}
	}
}

