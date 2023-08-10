#include "Weapons/SubActions/CSubAction_Sword.h"
#include "Global.h"
#include "Weapons/CAttachment.h"
#include "CSubAction_Fist.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Weapons/AddOns/CGhostTrail.h"

#include "Components/CMovementComponent.h"
#include "Weapons/CDoAction.h"


void UCSubAction_Sword::Pressed()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();

	State->SetActionMode();
	State->OnSubActionMode();

	GhostTrail = CHelpers::Play_GostTrail(GhostTrailClass, Owner);

	ActionData.DoAction(Owner);
}

void UCSubAction_Sword::Begin_SubAction_Implementation()
{
	Super::Begin_SubAction_Implementation();

	Attachment->OnAttachmentBeginOverlap.Remove(DoAction, "OnAttachmentEndCollision");
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &UCSubAction_Sword::OnAttachmentBeginOverlap);

	bMoving = true;

	Start = Owner->GetActorLocation();
	End = Start + Owner->GetActorForwardVector() * Distance;


	float radius = Owner->GetCapsuleComponent()->GetScaledCapsuleRadius();
	float height = Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FRotator rotation = Owner->GetActorRotation();

	TArray<AActor*> ignores;
	ignores.Add(Owner);

	TArray<FHitResult> hitResults;
	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery3);

	UKismetSystemLibrary::BoxTraceMultiForObjects(Owner->GetWorld(), Start, End, FVector(0, radius, height), rotation, objects, false, ignores, DrawDebug, hitResults, true);
	for(const FHitResult& hitResult : hitResults)
	{
		ACharacter* character = Cast<ACharacter>(hitResult.GetActor());

		if(!!character)
		{
			character->GetCapsuleComponent()->SetCollisionProfileName("Sword_SubAction");

			Overlapped.Add(character);
		}
	}
	FHitResult lineHitResult;
	UKismetSystemLibrary::LineTraceSingle(Owner->GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, false, ignores, DrawDebug, lineHitResult, true);

	if(lineHitResult.bBlockingHit)
	{
		FVector direction = (End - Start).GetSafeNormal2D();
		End = lineHitResult.Location - (direction * radius * 2);

		if (DrawDebug == EDrawDebugTrace::ForDuration)
			DrawDebugSphere(Owner->GetWorld(), End, radius * 2, 20, FColor::Magenta, true, 2);
	}

	if (DrawDebug == EDrawDebugTrace::ForDuration)
		DrawDebugDirectionalArrow(Owner->GetWorld(), Start, End, 25, FColor::Green, true, 5, 3);
}

void UCSubAction_Sword::End_SubAction_Implementation()
{
	Super::End_SubAction_Implementation();

	Attachment->OnAttachmentBeginOverlap.Remove(this, "OnAttachmentEndCollision");
	Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);
		
	State->SetIdleMode();
	State->OffSubActionMode();

	Movement->Move();
	Movement->DisableFixedCamera();

	bMoving = false;

	for (ACharacter* character : Overlapped)
		character->GetCapsuleComponent()->SetCollisionProfileName("Pawn");

	GhostTrail->Destroy();
}

void UCSubAction_Sword::Tick_Implementation(float InDeltaTime)
{
	Super::Tick_Implementation(InDeltaTime);
	CheckFalse(bMoving);

	FVector location = Owner->GetActorLocation();
	float radius = Owner->GetCapsuleComponent()->GetScaledCapsuleRadius();

	if(location.Equals(End, radius))
	{
		bMoving = false;

		Start = End = Owner->GetActorLocation();
		return;
	}

	FVector direction = (End - Start).GetSafeNormal2D();
	Owner->AddActorWorldOffset(direction * Speed * InDeltaTime, true);
}

void UCSubAction_Sword::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	CheckNull(InOther);

	HitData.SendDamage(Owner, InAttackCuaser, InOther);
}