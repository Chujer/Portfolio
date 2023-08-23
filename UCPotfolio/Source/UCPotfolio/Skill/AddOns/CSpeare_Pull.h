#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpeare_Pull.generated.h"

UCLASS()
class UCPOTFOLIO_API ACSpeare_Pull : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpeare_Pull();

public:
	FORCEINLINE TArray<ACharacter*> GetTargets() { return Targets; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;



private:
	UPROPERTY(EditAnywhere)
		float RotInitSpeed;

	UPROPERTY(EditAnywhere)
		float RotMaxSpeed;
	
	UPROPERTY(EditAnywhere)
		float PullSpeed;

private:
	ACharacter* OwnerCharacter;
	TArray<FHitResult> HitResults;
	TArray<ACharacter*> Targets;
	TArray<AActor*> Ignores;
	FVector Start;

	float RotSpeed;
};
