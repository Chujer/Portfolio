#include "Skill/AddOns/CSpeare_Pull.h"
#include "Global.h"

ACSpeare_Pull::ACSpeare_Pull()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACSpeare_Pull::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerCharacter->GetAllChildActors(Ignores);
	Ignores.Add(OwnerCharacter);
	Start = OwnerCharacter->GetActorLocation();
	RotSpeed = RotInitSpeed;
}

void ACSpeare_Pull::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool result;

	result = UKismetSystemLibrary::SphereTraceMulti(OwnerCharacter->GetWorld(), Start, Start, 1000.0f, ETraceTypeQuery::TraceTypeQuery2, false, Ignores, EDrawDebugTrace::None, HitResults, true);

	CheckFalse(result);

	for (FHitResult hitResult : HitResults)		//범위내 적 회전하면서 끌어당기기
	{
		ACharacter* temp = Cast<ACharacter>(hitResult.Actor);
		if(!!temp)
		{
			Targets.AddUnique(temp);
			temp->CustomTimeDilation = 0.1f;
			FRotator rotator = FRotator::ZeroRotator;
			rotator.Yaw= UKismetMathLibrary::FindLookAtRotation(temp->GetActorLocation(), OwnerCharacter->GetActorLocation()).Yaw;
			
			temp->SetActorRotation(rotator);

			FVector rightVector = temp->GetActorRightVector();
			FVector fowardVector = temp->GetActorForwardVector();

			FVector moveVector = temp->GetActorLocation() + (rightVector * RotSpeed) ;

			if(GetDistanceTo(temp) > 400)
				moveVector = moveVector + (fowardVector *  PullSpeed);

			temp->SetActorLocation(moveVector);
			if (temp->GetCapsuleComponent()->GetCollisionProfileName() != "HitEnemy")
				temp->GetCapsuleComponent()->SetCollisionProfileName("HitEnemy");
		}
	}
}

