#include "Components/CTargettingComponent.h"
#include "Particles/ParticleSystem.h"
#include "Global.h"

UCTargettingComponent::UCTargettingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCTargettingComponent::Toggle_Target()
{
	if (IsValid(Target.Get()))
		EndTarget();
	else
		BeginTarget();
}

void UCTargettingComponent::BeginTarget()
{
	CLog::Print("Targetting");

	FVector start = OwnerCharacter->GetActorLocation();
	TArray<AActor*> Ignores;
	TArray<ACharacter*> targets;
	Ignores.Add(OwnerCharacter.Get());

	UKismetSystemLibrary::SphereTraceMulti(OwnerCharacter->GetWorld(), start, start, TargettingRange, TraceChannel, false,
		Ignores, EDrawDebugTrace::ForDuration, HitResults, true);
	for(FHitResult result : HitResults)
	{
		ACharacter* tempCharacter = Cast<ACharacter>(result.Actor);
		if (!tempCharacter)
			continue;

		targets.Add(tempCharacter);
	}

	if(targets.Num() > 0)
	{
		//입사각이 제일 작은 적을 타겟으로 설정
		ChangeTarget(CHelpers::NearyFromCameraFront(OwnerCharacter.Get(), targets));
	}
}

void UCTargettingComponent::EndTarget()
{
}

void UCTargettingComponent::ChangeTarget(ACharacter* target)
{
	if (!IsValid(target))
	{
		EndTarget();
		return;
	}
	if(!!ParticleComponent)
		ParticleComponent->DestroyComponent();
	ParticleComponent = CHelpers::PlayEffect(target->GetWorld(), Particle, FTransform::Identity, target->GetMesh(), FName("Root"));
	Target = target;
}


void UCTargettingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());	
}

void UCTargettingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

