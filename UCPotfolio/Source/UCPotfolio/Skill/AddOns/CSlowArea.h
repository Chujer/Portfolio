#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CSlowArea.generated.h"

UCLASS()
class UCPOTFOLIO_API ACSlowArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSlowArea();

public:
	virtual void BeginPlay() override;

	UFUNCTION()
		void Destroyed() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ScaleSettingSphere(float Output);


	UFUNCTION()
		void RemoveArea(bool bChargeSucced);
private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere,Category = "Setting")
		FVector AddScale;

	UPROPERTY(EditAnywhere, Category = "Setting")
		float SlowTime = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Setting")
		UMaterialParameterCollection* MaterialParmater;

	UPROPERTY(EditAnywhere, Category = "Curve")
		class UCurveFloat* Curve;

private:
	class ACharacter* Character;
	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;
	class UTimelineComponent* Timeline;
	class ACAttachment* Attachment;

	TArray<AActor*> TargetActors;
	FVector FirstScale;
	TArray<AActor*> Ignores;

	FOnTimelineEvent EndTimeLine;
};
