#include "Weapons/DoActions/CDoAction_Bow.h"
#include "Global.h"
#include "AIController.h"
#include "Weapons/CAttachment.h"
#include "Weapons/CAttachment_Bow.h"
#include "Weapons/AddOns/CProjectile.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CStateComponent.h"

UCDoAction_Bow::UCDoAction_Bow()
{
	CHelpers::GetClass<ACProjectile>(&ArrowClass, "Blueprint'/Game/Weapons/Bow/BP_CProjectile_Arrow.BP_CProjectile_Arrow_C'");
}

void UCDoAction_Bow::BeginPlay(ACAttachment* InAttachment, UCEquipment* InEquipment, ACharacter* InOwner,
	const TArray<FDoActionData>& InDoActionData, const TArray<FHitData>& InHitData)
{
	Super::BeginPlay(InAttachment, InEquipment, InOwner, InDoActionData, InHitData);

	SkeletalMesh = CHelpers::GetComponent<USkeletalMeshComponent>(InAttachment);
	PoseableMesh = CHelpers::GetComponent<UPoseableMeshComponent>(InAttachment);

	OriginLocation = PoseableMesh->GetBoneLocationByName("bow_string_mid", EBoneSpaces::ComponentSpace);

	ACAttachment_Bow* bow = Cast<ACAttachment_Bow>(InAttachment);
	Bending = bow->GetBend();
}

void UCDoAction_Bow::DoAction()
{
	CheckFalse(State->IsIdleMode());

	//if(OwnerCharacter->GetController<AAIController>() == nullptr)
	CheckFalse(State->IsSubActionMode());

	Super::DoAction();

	DoActionDatas[0].DoAction(OwnerCharacter);

}

void UCDoAction_Bow::Begin_DoAction()
{
	Super::Begin_DoAction();

	ACProjectile* projectile = GetAttachedArrow();
	projectile->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

	projectile->OnHit.AddDynamic(this, &UCDoAction_Bow::OnArrowHit);
	projectile->OnEndPlay.AddDynamic(this, &UCDoAction_Bow::OnArrowEndPlay);

	FVector forward = FQuat(OwnerCharacter->GetControlRotation()).GetForwardVector();

	projectile->Shoot(forward);

	*Bending = 0;
	PoseableMesh->SetBoneLocationByName("bow_string_mid", OriginLocation, EBoneSpaces::ComponentSpace);
}

void UCDoAction_Bow::End_DoAction()
{
	Super::End_DoAction();

	*Bending = 1;
	CreateArrow();
}

void UCDoAction_Bow::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	bool bCheck = true;
	bCheck &= (bEndEquip == true);
	bCheck &= (bBeginAction == false);
	bCheck &= (bAttachedString == true);

	CheckFalse(bCheck);

	PoseableMesh->CopyPoseFromSkeletalComponent(SkeletalMesh);

	FVector handLocation = OwnerCharacter->GetMesh()->GetSocketLocation("Hand_Bow_Right");
	PoseableMesh->SetBoneLocationByName("Bow_string_mid", handLocation, EBoneSpaces::WorldSpace);
	
}

void UCDoAction_Bow::OnEquip()
{
	Super::OnEquip();

	bEndEquip = false;
}

void UCDoAction_Bow::OnBeginEquip()
{
	Super::OnBeginEquip();

	CreateArrow();

	OwnerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCDoAction_Bow::OnEndEquip()
{
	Super::OnEndEquip();
	bEndEquip = true;
}

void UCDoAction_Bow::OnBeginUnEquip()
{
	*Bending = 0;
	OwnerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	PoseableMesh->SetBoneLocationByName("bow_string_mid", OriginLocation, EBoneSpaces::ComponentSpace);

	for(int32 i = Arrows.Num() - 1; i>=0; i--)
	{
		if (!!Arrows[i]->GetAttachParentActor())
			Arrows[i]->Destroy();
	}
}

void UCDoAction_Bow::CreateArrow()
{
	if (World->bIsTearingDown == true)	//월드가 종료되었는지
		return;

	FTransform transform;
	ACProjectile* arrow = World->SpawnActorDeferred<ACProjectile>(ArrowClass, transform, NULL, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	CheckNull(arrow);

	arrow->AddIgnoreActor(OwnerCharacter);

	FAttachmentTransformRules rule = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
	arrow->AttachToComponent(OwnerCharacter->GetMesh(), rule, "Hand_Bow_Right_Arrow");

	Arrows.Add(arrow);
	UGameplayStatics::FinishSpawningActor(arrow, transform);
}

ACProjectile* UCDoAction_Bow::GetAttachedArrow()
{
	for (ACProjectile* projectile : Arrows)
	{
		if (!!projectile->GetAttachParentActor())
			return projectile;
	}

	return nullptr;
}

void UCDoAction_Bow::OnArrowHit(AActor* InCauser, ACharacter* InOtherCharacter)
{
	CheckFalse(HitDatas.Num() > 0);

	HitDatas[0].SendDamage(OwnerCharacter, InCauser, InOtherCharacter);
}

void UCDoAction_Bow::OnArrowEndPlay(ACProjectile* InDestroyer)
{
	Arrows.Remove(InDestroyer);
}