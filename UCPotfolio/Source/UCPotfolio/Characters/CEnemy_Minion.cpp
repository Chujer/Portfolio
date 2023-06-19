#include "Characters/CEnemy_Minion.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

ACEnemy_Minion::ACEnemy_Minion()
{
	SetMesh("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Dawn.Minion_Lane_Melee_Dawn'");

	GetCapsuleComponent()->SetCapsuleRadius(60.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(150.0f);

	GetMesh()->SetRelativeLocation(FVector(0,0,-150.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	GetMesh()->SetRelativeScale3D(FVector(1.5f, 1.5f, 2.0f));


	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "StateComponent");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &StatusComponent, "StatusComponent");

	SetOriginMaterials(GetMesh()->SkeletalMesh);
}

void ACEnemy_Minion::BeginPlay()
{
	Super::BeginPlay();
}

void ACEnemy_Minion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACEnemy_Minion::ApplyDamage(ACharacter* InAttacker, AActor* InAttackCauser, EDamageType InDamageType, float Power)
{
	IICharacter::ApplyDamage(InAttacker, InAttackCauser, InDamageType, Power);

	CheckNull(HitDataAssets);

	HitDataAssets->PlayHitMontage(this, InDamageType);
	StatusComponent->Damage(Power);
}


void ACEnemy_Minion::End_Hitted()
{

}

void ACEnemy_Minion::End_Dead()
{
}

void ACEnemy_Minion::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
