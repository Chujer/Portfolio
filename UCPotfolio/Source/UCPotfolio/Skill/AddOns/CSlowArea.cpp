#include "Skill/AddOns/CSlowArea.h"
#include "GameFramework/Character.h"
#include "Curves/CurveFloat.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Components/CWeaponComponent.h"
#include "Weapon/CAttachment.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollection.h"

ACSlowArea::ACSlowArea()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USphereComponent>(this, &Sphere, "Sphere");
	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline, "TimeLine");
}

void ACSlowArea::BeginPlay()
{
	Super::BeginPlay();
}

void ACSlowArea::BeginPlay(ACharacter* InCharacter)
{
	Character = InCharacter;
	Attachment = CHelpers::GetComponent<UCWeaponComponent>(Character)->GetAttachment();
	Sphere->SetHiddenInGame(false);
	Ignores.Add(Character);
	Ignores.Add(Attachment);
	if (!!Curve)
	{
		FOnTimelineFloat TimelineEvent;
		TimelineEvent.BindUFunction(this, "ScaleSettingSphere");

		if (!TimelineEvent.IsBound())
			CLog::Print("no");

		Timeline->AddInterpFloat(Curve, TimelineEvent);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(1);

		Timeline->PlayFromStart();
		FirstScale = GetActorScale3D();
	}

	if(!!Sphere)
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACSlowArea::OnComponentBeginOverlap);

	if (!Sphere->OnComponentBeginOverlap.IsBound())
		CLog::Print("No");
	EndTimeLine.BindDynamic(this, &ACSlowArea::Destroyed);
}

void ACSlowArea::Destroyed()
{
	Destroy();
}

void ACSlowArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACSlowArea::ScaleSettingSphere(float Output)
{
	FVector scale = UKismetMathLibrary::VLerp(FirstScale, AddScale, Output);
	SetActorScale3D(scale);
	if (!!MaterialParmater)
	{
		UKismetMaterialLibrary::SetVectorParameterValue(Character->GetWorld(), MaterialParmater, "Position", Character->GetActorLocation());
		UKismetMaterialLibrary::SetScalarParameterValue(Character->GetWorld(), MaterialParmater, "Radius", Output * 10.0f);
	}
}

void ACSlowArea::RemoveArea(bool bChargeSucced)
{
	if (!bChargeSucced)
	{
		if (!!MaterialParmater)
		{
			UKismetMaterialLibrary::SetScalarParameterValue(Character->GetWorld(), MaterialParmater, "Radius", 0);
		}
		TargetActors.Empty();

		Destroy();
	}
	else
	{
		FOnTimelineFloat TimelineEvent;
		TimelineEvent.BindUFunction(this, "ScaleSettingSphere");

		if (!TimelineEvent.IsBound())
			CLog::Print("no");

		Timeline->AddInterpFloat(Curve, TimelineEvent);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(1);

		Timeline->ReverseFromEnd();
		Timeline->SetTimelineFinishedFunc(EndTimeLine);
	}
}

void ACSlowArea::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckFalse(Ignores.Find(OtherActor) == -1);

	OtherActor->CustomTimeDilation =SlowTime;
	TargetActors.AddUnique(OtherActor);
}
