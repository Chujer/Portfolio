#include "Characters/CPlayer.h"
#include "Utilities/CHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CIdentityComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/CWeaponComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CRollComponent.h"
#include "Components/CParkourComponent.h"
#include "Components/CTargettingComponent.h"
#include "Utilities/CLog.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMesh("SkeletalMesh'/Game/Resource/CharacterAsset/Meshes/Characters/Combines/SK_Arashi_E.SK_Arashi_E'");
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());

	//카메라 설정
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateComponent<UCameraComponent>(this, &CineCamera, "CineCamera", SpringArm);
	//카메라 전환을 위한 UCHildActorComponent
	CHelpers::CreateComponent<UChildActorComponent>(this, &MainCamChildActorComponent, "MainCamChildActorComponent", Camera);
	CHelpers::CreateComponent<UChildActorComponent>(this, &CineCamChildActorComponent, "CineCamChildActorComponent", CineCamera);

	CHelpers::CreateActorComponent<UCMovementComponent>(this, &MovementComponent, "Movement");
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &WeaponComponent, "WeaponComponent");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "StateComponent");
	CHelpers::CreateActorComponent<UCRollComponent>(this, &RollComponent, "RollComponent");
	CHelpers::CreateActorComponent<UCIdentityComponent>(this, &IdentityComponent, "IdentityComponent");
	CHelpers::CreateActorComponent<UCParkourComponent>(this, &ParkourComponent, "ParkourComponent");
	CHelpers::CreateActorComponent<UCTargettingComponent>(this, &TargettingComponent, "TargettingComponent");
	CHelpers::CreateComponent<USceneComponent>(this, &ArrowGroup, "ArrowGroup", GetCapsuleComponent());

	//치장 (헬멧, 검집)
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
	CineCamera->SetRelativeLocation(FVector(-688.914917, 0.006348, 706.122803));
	CineCamera->SetRelativeRotation(FRotator(-30, 0, 0));

	CreateArrow();

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
//	PlayerInputComponent->BindAction("Sword", EInputEvent::IE_Pressed, WeaponComponent,&UCWeaponComponent::Released);
	PlayerInputComponent->BindAction("Spear", EInputEvent::IE_Pressed, WeaponComponent,&UCWeaponComponent::SetSpearMode);

	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoAction);

	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, RollComponent, &UCRollComponent::Roll);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, MovementComponent, &UCMovementComponent::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, MovementComponent, &UCMovementComponent::OffSprint);

	PlayerInputComponent->BindAction<TDelegate<void(ESkillIndex)>>("SkillF", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkill,ESkillIndex::F);
	PlayerInputComponent->BindAction<TDelegate<void(ESkillIndex)>>("SkillR", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkill,ESkillIndex::R);
	PlayerInputComponent->BindAction<TDelegate<void(ESkillIndex)>>("SkillV", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkill,ESkillIndex::V);
	PlayerInputComponent->BindAction<TDelegate<void(ESkillIndex)>>("SkillE", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkill,ESkillIndex::E);
	PlayerInputComponent->BindAction<TDelegate<void(ESkillIndex)>>("SkillQ", EInputEvent::IE_Pressed, WeaponComponent, &UCWeaponComponent::DoSkill,ESkillIndex::Q);

	PlayerInputComponent->BindAction("Identity", EInputEvent::IE_Pressed, IdentityComponent, &UCIdentityComponent::DoIdentity);
	PlayerInputComponent->BindAction("Targetting", EInputEvent::IE_Pressed, TargettingComponent, &UCTargettingComponent::BeginTarget);

	PlayerInputComponent->BindAction("SkillF", EInputEvent::IE_Released, WeaponComponent, &UCWeaponComponent::Released);
	PlayerInputComponent->BindAction("SkillR", EInputEvent::IE_Released, WeaponComponent, &UCWeaponComponent::Released);
	PlayerInputComponent->BindAction("SkillV", EInputEvent::IE_Released, WeaponComponent, &UCWeaponComponent::Released);
	PlayerInputComponent->BindAction("SkillE", EInputEvent::IE_Released, WeaponComponent, &UCWeaponComponent::Released);

}


void ACPlayer::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	ParkourComponent->DoParkour(true);
}

void ACPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (MovementComponent->CanMove())
		CLog::Print("true", 20);
	else
		CLog::Print("false", 20);
}

void ACPlayer::CreateArrow()
{
	Arrows.SetNum((int32)EParkourArrowType::Max);

	for(int32 i = 0; i< Arrows.Num(); i++)
	{
		FString name = StaticEnum<EParkourArrowType>()->GetNameStringByIndex(i);
		CHelpers::CreateComponent<UArrowComponent>(this, &Arrows[i], FName(name), ArrowGroup);

		switch ((EParkourArrowType)i)
		{
		case EParkourArrowType::Center:
			Arrows[i]->ArrowColor = FColor::Red;
			break;
		case EParkourArrowType::Ceil:
			Arrows[i]->ArrowColor = FColor::Green;
			Arrows[i]->SetRelativeLocation(FVector(0, 0, 100));
			break;
		case EParkourArrowType::Floor:
			Arrows[i]->ArrowColor = FColor::Blue;
			Arrows[i]->SetRelativeLocation(FVector(0, 0, -80));
			break;

		case EParkourArrowType::Left:
			Arrows[i]->ArrowColor = FColor::Magenta;
			Arrows[i]->SetRelativeLocation(FVector(0, -30, 0));
			break;

		case EParkourArrowType::Right:
			Arrows[i]->ArrowColor = FColor::Magenta;
			Arrows[i]->SetRelativeLocation(FVector(0, 30, 0));
			break;

		case EParkourArrowType::Land:
			Arrows[i]->ArrowColor = FColor::Yellow;
			Arrows[i]->SetRelativeLocation(FVector(200, 0, 100));
			Arrows[i]->SetRelativeRotation(FRotator(-90, 0, 0));
			break;
		}
	}
}


