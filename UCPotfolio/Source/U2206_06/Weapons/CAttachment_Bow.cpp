#include "Weapons/CAttachment_Bow.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Global.h"
#include "Characters/CAnimInstance.h"
#include "Characters/CAnimInstance_Bow.h"



ACAttachment_Bow::ACAttachment_Bow()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &SkeletaMesh, "SkeletaMesh", Root);
	CHelpers::CreateComponent<UPoseableMeshComponent>(this, &PoseableMesh, "PoseableMesh", Root);

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Weapons/ElvenBow/SK_ElvenBow.SK_ElvenBow'");
	SkeletaMesh->SetSkeletalMesh(mesh);
	SkeletaMesh->SetCollisionProfileName("NoCollision");

	TSubclassOf<UCAnimInstance_Bow> animInstance;
	CHelpers::GetClass<UCAnimInstance_Bow>(&animInstance, "AnimBlueprint'/Game/Weapons/Bow/ABP_Bow.ABP_Bow_C'");
	SkeletaMesh->SetAnimInstanceClass(animInstance);
}

void ACAttachment_Bow::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//PoseableMesh->CopyPoseFromSkeletalComponent(SkeletaMesh);


}

void ACAttachment_Bow::BeginPlay()
{
	Super::BeginPlay();

	AttachTo("Holster_Bow");

	SkeletaMesh->SetVisibility(false);

	PoseableMesh->SetSkeletalMesh(SkeletaMesh->SkeletalMesh);
	PoseableMesh->CopyPoseFromSkeletalComponent(SkeletaMesh);

	UCAnimInstance_Bow* instance = Cast<UCAnimInstance_Bow>(SkeletaMesh->GetAnimInstance());
}

void ACAttachment_Bow::OnBeginEquip_Implementation()
{
	Super::OnBeginEquip_Implementation();

	AttachTo("Hand_Bow_Left");

	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();
	if(!!controller)
	{
		OriginViewPitchRange.X = controller->PlayerCameraManager->ViewPitchMin = ViewPitchRange.X;
		OriginViewPitchRange.Y = controller->PlayerCameraManager->ViewPitchMin = ViewPitchRange.X;
		controller->PlayerCameraManager->ViewPitchMin = ViewPitchRange.X;
		controller->PlayerCameraManager->ViewPitchMax = ViewPitchRange.Y;
	}
}

void ACAttachment_Bow::OnUnEquip_Implementation()
{
	Super::OnUnEquip_Implementation();

	AttachTo("Holster_Bow");

	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();
	if (!!controller)
	{
		controller->PlayerCameraManager->ViewPitchMin = OriginViewPitchRange.X;
		controller->PlayerCameraManager->ViewPitchMax = OriginViewPitchRange.Y;
	}
}

float* ACAttachment_Bow::GetBend()
{
	return Cast<UCAnimInstance_Bow>(SkeletaMesh->GetAnimInstance())->GetBend();
}