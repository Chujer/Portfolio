#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPatrolPath.generated.h"

UCLASS()
class U2206_06_API ACPatrolPath : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Loop")
		bool bLoop;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere, Category = "Path")
		int32 Index;

	UPROPERTY(EditAnywhere, Category = "Path")
		bool bReverse;

	UPROPERTY(EditAnywhere, Category = "Path")
		float AcceptanceDistance = 10;
public:
	FORCEINLINE class USplineComponent* GetSpline() { return Spline; }

public:	
	ACPatrolPath();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

public:
	FVector GetMoveTo();
	void UpdateIndex();
};
