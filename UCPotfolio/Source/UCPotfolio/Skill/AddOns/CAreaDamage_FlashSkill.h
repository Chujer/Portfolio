#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Skill/AddOns/CAreaDamage.h"
#include "CAreaDamage_FlashSkill.generated.h"

UCLASS()
class UCPOTFOLIO_API ACAreaDamage_FlashSkill : public ACAreaDamage
{
	GENERATED_BODY()

public:
	ACAreaDamage_FlashSkill();
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
		void ScaleUp(float time);

	void EndChargeDestroy();
protected:
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere)
		float UpScale = 1250;

	UPROPERTY(EditAnywhere)
		bool bHide = true;

	UPROPERTY(EditAnywhere, Category = "Curve")
		class UCurveFloat* Curve;

	FVector EndLocation;
	FTransform StartTrasnform;

private:
	TArray<ACharacter*> Targets;

private:


	FTimeline TimeLine;
};
