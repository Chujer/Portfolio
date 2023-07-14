#include "Skill/AddOns/CSlowArea.h"
#include "GameFramework/Character.h"
#include "Curves/CurveFloat.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

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
	Sphere->SetHiddenInGame(false);
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
}

void ACSlowArea::Destroyed()
{
	Super::Destroyed();
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

		for( AActor* target : TargetActors)
		{
			IICharacter* iCharacter = Cast<IICharacter>(target);
			iCharacter->ApplyDamageTimer(Character, nullptr, EDamageType::NORMAL, EDamageType::NORMAL, 10, 50, 0.2f, 0.7);
		}
	}
}

void ACSlowArea::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == Character);
	CheckFalse(TargetActors.Find(OtherActor) == -1);
	CLog::Print("CSlowAreaBeginOverlap");

	OtherActor->CustomTimeDilation =SlowTime;
	TargetActors.AddUnique(OtherActor);
}
