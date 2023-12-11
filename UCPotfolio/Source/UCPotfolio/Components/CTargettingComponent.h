#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CTargettingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPOTFOLIO_API UCTargettingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCTargettingComponent();

public:
	void Toggle_Target();
	void BeginTarget();
	void EndTarget();
	void ChangeTarget(ACharacter* target);
	void TickTargetting(float DeltaTime);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	TWeakObjectPtr<class ACharacter> OwnerCharacter;
	TWeakObjectPtr<class ACharacter> Target;
	TArray<FHitResult> HitResults;

private:
	bool MovingFocus = false;

public:
	UPROPERTY(EditAnywhere, Category = "setting")
		float FinishAngle = 2.0f;
		UPROPERTY(EditAnywhere, Category = "setting")
		float InterpSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "setting")
		float TargettingRange = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "setting")
		TEnumAsByte<ETraceTypeQuery> TraceChannel;

};
