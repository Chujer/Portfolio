#include "Skill/AddOns/CAreaDamage_FlashSkill.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"

ACAreaDamage_FlashSkill::ACAreaDamage_FlashSkill()
{
	UBoxComponent* boxComponent;
	CHelpers::CreateActorComponent<UBoxComponent>(this, &boxComponent, "BoxCollision");
//	boxComponent->SetRelativeLocation(FVector(0, 0, 20));
	MainCollision = boxComponent;
}

void ACAreaDamage_FlashSkill::BeginPlay()
{
	Super::BeginPlay();

	MainCollision->OnComponentBeginOverlap.AddDynamic(this, &ACAreaDamage_FlashSkill::OnComponentBeginOverlap);
	MainCollision->SetRelativeScale3D(FVector(1, 10, 14));
	MainCollision->SetHiddenInGame(bHide);

	StartTrasnform.SetScale3D(GetActorScale());
	StartTrasnform.SetLocation(GetActorLocation() + FVector(0,0,100));
	EndLocation = GetActorLocation() + (GetActorForwardVector() * UpScale) + FVector(0, 0, 100);


	FOnTimelineFloat timeline;
	timeline.BindUFunction(this, "ScaleUp");

	TimeLine.AddInterpFloat(Curve, timeline);
	TimeLine.PlayFromStart();
}

void ACAreaDamage_FlashSkill::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TimeLine.TickTimeline(DeltaSeconds);
}


void ACAreaDamage_FlashSkill::ScaleUp(float time)
{
	float setScale = UKismetMathLibrary::Lerp(StartTrasnform.GetScale3D().X, UpScale,time);
	FVector setLocation = UKismetMathLibrary::VLerp(StartTrasnform.GetLocation(),EndLocation, time);
	CLog::Print(time, 2);
	CLog::Print(setScale,3);

	UBoxComponent* Box = Cast<UBoxComponent>(MainCollision);

	Box->SetBoxExtent(FVector(setScale, 15, 15));

	SetActorLocation(setLocation);
}

void ACAreaDamage_FlashSkill::EndChargeDestroy()
{
	for (ACharacter* target : Targets)
	{
		IICharacter* iCharacter = Cast<IICharacter>(target);
		iCharacter->ApplyDamageTimer(Character, Cast<AActor>(Attachment), EDamageType::NORMAL, EDamageType::NORMAL, 10, 50, 0.2f, 0.7);
	}
	Destroy();
}

void ACAreaDamage_FlashSkill::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	CheckFalse(Ignores.Find(OtherActor) == -1);
	CheckNull(Cast<ACharacter>(OtherActor));

	Targets.AddUnique(Cast<ACharacter>(OtherActor));
}
