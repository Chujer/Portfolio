#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CTraceSpear.generated.h"

UCLASS()
class UCPOTFOLIO_API ACTraceSpear : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTraceSpear();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetBezierPoint();

private:
	void SetTargets();
	void SetLookTarget();

private:
	UFUNCTION()
		void Move(float time);
	UFUNCTION()
		void OnEndMove();

public:
	UPROPERTY(EditAnywhere, Category = "MeshComponent")
		class UStaticMeshComponent* SM_Spear;

	UPROPERTY(EditAnywhere, Category = "Effect")
		TArray<UFXSystemAsset*> SpearEffect;

	UPROPERTY(EditAnywhere, Category = "Curve")
		class UCurveFloat* Curve;

	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* MoveSound;


	UPROPERTY(EditAnywhere, Category = "Setting")
		float Range = 0;

	UPROPERTY(EditAnywhere, Category = "Setting")
		TEnumAsByte<EDrawDebugTrace::Type> DebugMode;

	UPROPERTY(EditAnywhere, Category = "Setting")
		TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(EditAnywhere, Category = "Setting")
		float Damage = 0;

private:
	UPROPERTY()
		class USceneComponent* root;

	UPROPERTY()
		TArray<ACharacter*> targets;
	UPROPERTY()
		ACharacter* CurTarget;

private:
	int32 curIndex = 0;

	FVector StartPos = FVector::ZeroVector;
	FVector SelfMovePoint = FVector::ZeroVector;

	FVector BezierPointVector = FVector::ZeroVector;	//베지어곡선 중간포인트
	FVector BezierMovePointVector = FVector::ZeroVector;	//이동될 중간포인트
	FVector EndPos = FVector::ZeroVector;

private:
	FTimeline Timeline;

	ACharacter* Hitted;
	class ACAttachment* Attachment;
	class ACPlayer* Character;
};

