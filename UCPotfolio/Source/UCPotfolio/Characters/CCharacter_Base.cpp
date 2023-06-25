#include "CCharacter_Base.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Utilities/CHelpers.h"
#include "Utilities/CLog.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "GameFramework/CharacterMovementComponent.h"
//#include "Camera/CameraComponent.h"

ACCharacter_Base::ACCharacter_Base()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
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


