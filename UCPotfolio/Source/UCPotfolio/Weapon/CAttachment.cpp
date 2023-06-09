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
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	//소유 콜리전 담기
	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);	//bincludeAllDescendants : 자녀 목록에 모든 자손을 포함할지 정한다.
	for(USceneComponent* child : children)
	{
		UShapeComponent* shape = Cast<UShapeComponent>(child);

		if(!!shape)
		{
			Collision.Add(shape);
			CLog::Print(shape->GetName(), -1, 5, FColor::Red);
		}
	}
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

