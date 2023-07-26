#include "Characters/CPlayer.h"
#include "Utilities/CHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CRollComponent.h"
#include "Skill/CSkill.h"
#include "Utilities/CLog.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMesh("SkeletalMesh'/Game/Resource/CharacterAsset/Meshes/Characters/Combines/SK_Arashi_E.SK_Arashi_E'");
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	CHelpers::CreateActorComponent<UCMovementComponent>(this, &MovementComponent, "Movement");
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &WeaponComponent, "WeaponComponent");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "StateComponent");
	CHelpers::CreateActorComponent<UCRollComponent>(this, &RollComponent, "RollComponent");

	//Ä¡Àå (Çï¸ä, °ËÁý)
	USkeletalMeshComponent* helmet;
	USkeletalMesh* helmetMesh;
	CHelpers::GetAsset(&helmetMesh, "SkeletalMesh'/Game/Resource/CharacterAsset/Meshes/Characters/Separates/Acessories/SK_AHat.SK_AHat'");
	CHelpers::CreateActorComponent<USkeletalMeshComponent>(this, &helmet, "Helmet");

	helmet->SetSkeletalMesh(helmetMesh);
	helmet->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Helmet");
	helmet->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	USkeletalMeshComponent* holster;
	USkeletalMesh* holsterMesh;
	CHelpers::GetAsset(&holsterMesh, "SkeletalMesh'/Game/Resource/CharacterAsset/Meshes/Weapons/SK_L_KatanaCover.SK_L_KatanaCover'");
	CHelpers::CreateActorComponent<USkeletalMeshComponent>(this, &holster, "Holster");

	holster->SetSkeletalMesh(holsterMesh);
	holster->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Holster_Sword");
	holster->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 400;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	GetCapsuleComponent()->SetCollisionProfileName("Player");
	GetMesh()->SetCollisionProfileName("OverlapAll");

	Camera->SetRelativeLocation(FVector(0, 0, 80));

	CheckNull(MovementComponent);

	MovementComponent->OffSprint();
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->SetUseControllYaw(false);

}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", MovementComponent, &UCMovementComponent::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", MovementComponent, &UCMovementComponent::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", MovementComponent, &UCMovementComponent::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", MovementComponent, &UCMovementComponent::OnVerticallLook);

	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, WeaponComponent,&UCWeaponComponent::SetSwordMode);
	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, WeaponComponent,&UCWeaponComponent::Released);

	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoAction);

	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, RollComponent, &UCRollComponent::Roll);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, MovementComponent, &UCMovementComponent::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, MovementComponent, &UCMovementComponent::OffSprint);

	PlayerInputComponent->BindAction("SkillF", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkillF);
	PlayerInputComponent->BindAction("SkillR", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkillR);
	PlayerInputComponent->BindAction("SkillV", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkillV);
	PlayerInputComponent->BindAction("SkillE", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkillE);
	PlayerInputComponent->BindAction("SkillQ", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkillQ);

	PlayerInputComponent->BindAction("SkillF", EInputEvent::IE_Released, WeaponComponent, &UCWeaponComponent::Released);
	PlayerInputComponent->BindAction("SkillR", EInputEvent::IE_Released, WeaponComponent, &UCWeaponComponent::Released);
	PlayerInputComponent->BindAction("SkillV", EInputEvent::IE_Released, WeaponComponent, &UCWeaponComponent::Released);
	PlayerInputComponent->BindAction("SkillE", EInputEvent::IE_Released, WeaponComponent, &UCWeaponComponent::Released);
}

void ACPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (MovementComponent->CanMove())
		CLog::Print("true", 20);
	else
		CLog::Print("false", 20);

}
