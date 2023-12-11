#include "CCharacter_Base.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Components/CGravityComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetComponent.h"
#include "Utilities/CHelpers.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "Camera/CameraComponent.h"

ACCharacter_Base::ACCharacter_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateActorComponent<UCGravityComponent>(this, &GravityComponent, "GravityComponent");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &StatusComponent, "StatusComponent");
	CHelpers::CreateComponent<UWidgetComponent>(this, &LockOnWidget, "LockOnWidget", GetCapsuleComponent());
}

void ACCharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	LockOnWidget->SetVisibility(false);
}

void ACCharacter_Base::SetMesh(FString InPath)
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, InPath);
	GetMesh()->SetSkeletalMesh(mesh);
	SetOriginMaterials(mesh);

	GetCapsuleComponent()->SetCollisionProfileName("Enemy");
	GetMesh()->SetCollisionProfileName("OverlapAll");
}

void ACCharacter_Base::SetLockOnVisible(bool InBool)
{
	LockOnWidget->SetVisibility(InBool);
}

void ACCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACCharacter_Base::SetOriginMaterials(USkeletalMesh* InSkeletaMesh)
{
	
	for(int i =0; i< InSkeletaMesh->Materials.Num(); i++)
	{
		OriginMaterials.Add(InSkeletaMesh->Materials[i]);
	}
}

void ACCharacter_Base::SetMaterialToOrigin()
{
	for(int i = 0; i < OriginMaterials.Num(); i++)
	{
		GetMesh()->SkeletalMesh->Materials[i] = OriginMaterials[i];
	}
}


