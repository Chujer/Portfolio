#include "Skill/AddOns/CAreaDamage_FlashSkill.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"

ACAreaDamage_FlashSkill::ACAreaDamage_FlashSkill()
{
	UBoxComponent* boxComponent;
	CHelpers::CreateActorComponent<UBoxComponent>(this, &boxComponent, "BoxCollision");
	MainCollision = boxComponent;
}

void ACAreaDamage_FlashSkill::BeginPlay()
{
	Super::BeginPlay();

	MainCollision->OnComponentBeginOverlap.AddDynamic(this, &ACAreaDamage_FlashSkill::OnComponentBeginOverlap);
	StartTrasnform.SetScale3D(GetActorScale());
	StartTrasnform.SetLocation(GetActorLocation());
	EndLocation = GetActorLocation() + GetActorForwardVector() * UpScale;
	MainCollision->SetRelativeScale3D(FVector(1, 1, 14));
}

void ACAreaDamage_FlashSkill::BeginPlay(ACharacter* InCharacter)
{
	Super::BeginPlay(InCharacter);
}

void ACAreaDamage_FlashSkill::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float setScale = UKismetMathLibrary::Lerp(StartTrasnform.GetScale3D().X, UpScale, DeltaSeconds);
	FVector setLocation = UKismetMathLibrary::VLerp(StartTrasnform.GetLocation(), EndLocation, DeltaSeconds);

	SetActorScale3D(FVector(setScale, 15, 15));
	SetActorLocation(setLocation);
}

void ACAreaDamage_FlashSkill::Destroyed()
{
	Super::Destroyed();

	for (AActor* target : TargetActors)
	{
		target->CustomTimeDilation = 1.0f;
		IICharacter* iCharacter = Cast<IICharacter>(target);
		iCharacter->ApplyDamageTimer(Character, Attachment, EDamageType::NORMAL, EDamageType::NORMAL, 10, 50, 0.2f, 0.7);
	}
}

void ACAreaDamage_FlashSkill::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	CheckFalse(Ignores.Find(OtherActor) == -1);
	
	TargetActors.AddUnique(OtherActor);
}
