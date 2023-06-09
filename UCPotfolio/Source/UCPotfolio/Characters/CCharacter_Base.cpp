#include "CCharacter_Base.h"
#include "Global.h"
#include "Utilities/CHelpers.h"
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
}

void ACCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

