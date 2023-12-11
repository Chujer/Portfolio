#include "Components/CTargettingComponent.h"

#include "CStateComponent.h"
#include "Particles/ParticleSystem.h"
#include "Global.h"
#include "Characters/CCharacter_Base.h"
#include "Components/WidgetComponent.h"

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

	if (!!Target.Get() && targets.Find(Target.Get()) != INDEX_NONE)
	{
		targets.RemoveSingle(Target.Get());
	}
	if (targets.Num() > 0)
	{
		//�Ի簢�� ���� ���� ���� Ÿ������ ����
		ChangeTarget(CHelpers::NearyFromCameraFront(OwnerCharacter.Get(), targets));
	}
}

void UCTargettingComponent::EndTarget()
{
	CheckNull(Target.Get());
	Cast<ACCharacter_Base>(Target)->SetLockOnVisible(false);
	Target = nullptr;
}

void UCTargettingComponent::ChangeTarget(ACharacter* target)
{
	if(!!Target.Get())
		Cast<ACCharacter_Base>(Target)->SetLockOnVisible(false);

	if (!IsValid(target))
	{
		EndTarget();
		return;
	}
	Target = target;
	Cast<ACCharacter_Base>(Target)->SetLockOnVisible(true);
}

void UCTargettingComponent::TickTargetting(float DeltaTime)
{
	FRotator ControlRotation;
	FRotator OwnerToTarget;

	ControlRotation = OwnerCharacter->GetControlRotation();
	OwnerToTarget = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), Target->GetActorLocation());
	OwnerToTarget.Pitch = ControlRotation.Pitch;			

	if(UKismetMathLibrary::EqualEqual_RotatorRotator(ControlRotation, OwnerToTarget, FinishAngle))
	{
		OwnerCharacter->GetController()->SetControlRotation(OwnerToTarget);
		if (MovingFocus)
			MovingFocus = false;
	}
	else
	{
		FRotator tempRot;
		tempRot = OwnerToTarget;
		tempRot.Pitch = OwnerToTarget.Pitch;

		FRotator EndRot;
		EndRot = UKismetMathLibrary::RInterpTo(ControlRotation, tempRot, DeltaTime, InterpSpeed);
		OwnerCharacter->GetController()->SetControlRotation(EndRot);
	}
}


void UCTargettingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());	
}

void UCTargettingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckNull(Target);	//Ÿ�� ������ �ȵ������� return
	CheckTrue(CHelpers::GetComponent<UCStateComponent>(OwnerCharacter)->IsDeadMode());	//�÷��̾� ������ return
	CheckTrue(OwnerCharacter->GetDistanceTo(Target.Get()) >= TargettingRange);	//�÷��̾�, ���� �Ÿ��� ������������ �ָ� return

	TickTargetting(DeltaTime);
}

