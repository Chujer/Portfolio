#include "Identity/CIdentity_SwordDash.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Global.h"
#include "Components/TimelineComponent.h"

void UCIdentity_SwordDash::BeginPlay(ACAttachment* InAttachment, ACharacter* InCharacter)
{
	UCIdentity::BeginPlay(InAttachment, InCharacter);
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
		ETraceTypeQuery::TraceTypeQuery1, false, ignores, EDrawDebugTrace::ForOneFrame, hitResult, true);

	if(hitResult.bBlockingHit)
	{
		EndPoint = hitResult.ImpactPoint;
		FTimeline Timeline;
		Timeline.SetFloatCurve(NormalCurve, "DashTimeLine");
		Timeline.PlayFromStart();
	}


}

void UCIdentity_SwordDash::DashTimeLine(float Output)
{
	a += Output;
	CLog::Print(a, 2);
}
