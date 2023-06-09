#include "Characters/CPlayer.h"
#include "Utilities/CHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/CWeaponComponent.h"

ACPlayer::ACPlayer()
{
	SetMesh("SkeletalMesh'/Game/Resource/CharacterAsset/Meshes/Characters/Combines/SK_Arashi_E.SK_Arashi_E'");
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());

	CHelpers::CreateActorComponent<UCMovementComponent>(this, &Movement, "Movement");
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &WeaponComponent, "WeaponComponent");
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 400;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraRotationLag = true;

	Camera->SetRelativeLocation(FVector(0, 0, 80));
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", Movement, &UCMovementComponent::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", Movement, &UCMovementComponent::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", Movement, &UCMovementComponent::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", Movement, &UCMovementComponent::OnVerticallLook);

	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, WeaponComponent,&UCWeaponComponent::SetSwordMode);
}
