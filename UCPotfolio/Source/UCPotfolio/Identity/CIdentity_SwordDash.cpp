#include "Identity/CIdentity_SwordDash.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Global.h"
#include "Components/TimelineComponent.h"

UCIdentity_SwordDash::UCIdentity_SwordDash()
{
}

void UCIdentity_SwordDash::BeginPlay(ACAttachment* InAttachment, ACharacter* InCharacter)
{
	UCIdentity::BeginPlay(InAttachment, InCharacter);
}

void UCIdentity_SwordDash::DoIdentityMontage()
{
	Super::DoIdentityMontage();

	OwnerCharacter->PlayAnimMontage(AnimMontage);
}

void UCIdentity_SwordDash::DoIdentity()
{
	UCIdentity::DoIdentity();


	FVector start = OwnerCharacter->GetActorLocation();
	FVector end = OwnerCharacter->GetControlRotation().Quaternion().GetForwardVector();
	end.Z = UKismetMathLibrary::Clamp(end.Z, 0, end.Z);
	end = end * DashRange;
	end = end + start;
	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);
	FHitResult hitResult;

	UKismetSystemLibrary::BoxTraceSingle(OwnerCharacter->GetWorld(), start, end, CollisionRange, FRotator::ZeroRotator,
		ETraceTypeQuery::TraceTypeQuery1, false, ignores, EDrawDebugTrace::None, hitResult, true);

	if(hitResult.bBlockingHit)
	{
		EndPoint = hitResult.ImpactPoint;
		Target = Cast<IICharacter>(hitResult.GetActor());
		FOnTimelineFloat timelineEvent;
		timelineEvent.BindUFunction(this, "DashTimeLine");
		Timeline.AddInterpFloat(NormalCurve, timelineEvent);
		Timeline.PlayFromStart();
	}
	else
	{
		EndPoint = end;
		FOnTimelineFloat timelineEvent;
		timelineEvent.BindUFunction(this, "DashTimeLine");
		Timeline.AddInterpFloat(NormalCurve, timelineEvent);
		Timeline.PlayFromStart();
	}


}

void UCIdentity_SwordDash::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	Timeline.TickTimeline(InDeltaTime);
}

void UCIdentity_SwordDash::DashTimeLine(float time)
{
	MovePos = UKismetMathLibrary::VLerp(OwnerCharacter->GetActorLocation(), EndPoint, time);

	OwnerCharacter->SetActorLocation(MovePos);


	if(UKismetMathLibrary::Vector_Distance(OwnerCharacter->GetActorLocation(), EndPoint) < 100)
	{
		OwnerCharacter->StopAnimMontage(OwnerCharacter->GetCurrentMontage());

		if (!!Target)
			Target->ApplyDamage(OwnerCharacter, (AActor*)Attachment, EDamageType::BACK_NOCKDOWN_IP, 0);

		Target = nullptr;
		Timeline.Stop();
	}
}
