#include "Characters/CEnemy_Minion.h"
#include "Global.h"
#include "Components/CapsuleComponent.h"
#include "Components/CGravityComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utilities/CLog.h"

ACEnemy_Minion::ACEnemy_Minion()
{

	SetMesh("SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Dawn.Minion_Lane_Melee_Dawn'");

	GetCapsuleComponent()->SetCapsuleRadius(60.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(150.0f);

	GetMesh()->SetRelativeLocation(FVector(0,0,-150.0f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	GetMesh()->SetRelativeScale3D(FVector(1.5f, 1.5f, 2.0f));

	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "StateComponent");

	SetOriginMaterials(GetMesh()->SkeletalMesh);
}

void ACEnemy_Minion::BeginPlay()
{
	Super::BeginPlay();
	CHelpers::GetComponent<UCGravityComponent>(this)->OnEndZeroGravity.AddDynamic(this, &ACEnemy_Minion::OnEndZeroGravity);
}

void ACEnemy_Minion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACEnemy_Minion::ApplyDamage(ACharacter* InAttacker, AActor* InAttackCauser, EDamageType InDamageType, float Power)
{
	IICharacter::ApplyDamage(InAttacker, InAttackCauser, InDamageType, Power);

	CheckNull(HitDataAssets);

	StatusComponent->Damage(Power);

	if (StatusComponent->GetHealth() <= 0.0f)
	{
		StateComponent->SetDeadMode();
		Destroy();
		return;
	}

	if (!!InAttacker)
	{
		//공격자 방향 보기
		FVector start = GetActorLocation();
		FVector target = InAttacker->GetActorLocation();

		FRotator rotate = FRotator::ZeroRotator;
		rotate.Yaw = UKismetMathLibrary::FindLookAtRotation(start, target).Yaw;

		SetActorRotation(rotate);
	}
	HitDataAssets->PlayHitEffect(this, InDamageType);

	StateComponent->SetHittedMode();
	
	GetCapsuleComponent()->SetCollisionProfileName("HitEnemy");

	HitDataAssets->PlayHitMontage(this, InDamageType);

	FString EnumToString = TEXT("Invalid");
	const UEnum* temp = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDamageType"), true);
	EnumToString = temp->GetNameStringByValue((int64)InDamageType);

	CLog::Print( EnumToString);
}

void ACEnemy_Minion::ApplyDamageTimer(ACharacter* InAttacker, AActor* InAttackCauser, EDamageType InNormalDamageType,
	EDamageType InLastDamageType, float InNormalPower, float InLastPower, float Interval, float EndTime)
{
	Attacker = InAttacker;
	AttackCauser = InAttackCauser;
	NormalDamageType = InNormalDamageType;
	LastDamageType = InLastDamageType;
	NormalDamagePower = InNormalPower;
	LastDamagePower = InLastPower;
	IICharacter::ApplyDamageTimer(InAttacker, InAttackCauser, InNormalDamageType, InLastDamageType, InNormalPower,
	                              InLastPower, Interval, EndTime);
	
	FTimerDelegate timerDelegate;
	FTimerDelegate timerDelegate2;

	timerDelegate.BindLambda([&]()
	{
		if(!!Attacker && InAttackCauser)
			ApplyDamage(Attacker, AttackCauser, NormalDamageType, NormalDamagePower);
	});

	timerDelegate2.BindLambda([&]()
	{
		if (!!Attacker && InAttackCauser)
		{
			ApplyDamage(Attacker, AttackCauser, LastDamageType, LastDamagePower);
		}
		GetWorld()->GetTimerManager().ClearTimer(timer);
		GetWorld()->GetTimerManager().ClearTimer(timer2);

		Attacker = nullptr;
		AttackCauser = nullptr;
	});

	GetWorld()->GetTimerManager().SetTimer(timer, timerDelegate, Interval, true);
	GetWorld()->GetTimerManager().SetTimer(timer2, timerDelegate2, EndTime, true);

}


void ACEnemy_Minion::End_Hitted()
{
	StateComponent->SetIdleMode();
	CheckTrue(StateComponent->IsAirComboMode());
	GetCapsuleComponent()->SetCollisionProfileName("Enemy");

}

void ACEnemy_Minion::End_Dead()
{
}

void ACEnemy_Minion::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CLog::Print((GetCapsuleComponent()->GetCollisionProfileName()).ToString(),2); 
}

void ACEnemy_Minion::OnEndZeroGravity()
{
	GetCapsuleComponent()->SetCollisionProfileName("Enemy");
}