#include "Weapon/CAttachment.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"
#include "Skill/CSkill.h"
#include "Skill/CSkill_Nomal.h"
#include "Utilities/CLog.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateComponent(this, &Root, "Root");

}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	//소유 콜리전 담기
	TArray<USceneComponent*> children;
	Root->GetChildrenComponents(true, children);	//bincludeAllDescendants : 자녀 목록에 모든 자손을 포함할지 정한다.
	for(USceneComponent* child : children)
	{
		UShapeComponent* shape = Cast<UShapeComponent>(child);

		if(!!shape)
		{
			shape->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
			shape->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);
			shape->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			Collisions.Add(shape);
		}
	}
	OffCollisions();

	OnEquipAnimPlay.AddDynamic(this, &ACAttachment::PlayEquipAnim);
	OnEquip.AddDynamic(this, &ACAttachment::OnBeginEquip);
	OnUnEquip.AddDynamic(this, &ACAttachment::OnBeginUnEquip);


	for (int32 i = 0; i < (int32)ESkillIndex::MAX; i++)
	{
		if (!!SkillsClass[i])
		{
			UCSkill* tempSkill = NewObject<UCSkill>(this, SkillsClass[i]);
			tempSkill->BeginPlay(Cast<ACPlayer>(OwnerCharacter), this);
			Skills[i] = tempSkill;
		}
	}

	Super::BeginPlay();
}


void ACAttachment::PlayEquipAnim()
{
	if (!!OwnerCharacter.Get() && !!EquipData.Montage)
		EquipData.PlayAnim(OwnerCharacter.Get());
	else
		OnBeginEquip();
}

void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::AttachToCollision(FName InSocketName)
{
	for(UShapeComponent* collision : Collisions)
	{
		if(collision->GetName() == InSocketName.ToString())
		{
			collision->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
			return;
		}
	}
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentBeginOverlap.IsBound())
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter.Get(), this, Cast<ACharacter>(OtherActor));
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass());

	if (OnAttachmentEndOverlap.IsBound())
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter.Get(), Cast<ACharacter>(OtherActor));
}

void ACAttachment::OnCollisions()
{
	if (OnAttachmentBeginCollision.IsBound())
		OnAttachmentBeginCollision.Broadcast();

	for (UShapeComponent* shape : Collisions)
		shape->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACAttachment::OffCollisions()
{
	if (OnAttachmentEndCollision.IsBound())
		OnAttachmentEndCollision.Broadcast();

	for (UShapeComponent* shape : Collisions)
		shape->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

