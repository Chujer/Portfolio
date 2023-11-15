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
	//TODO : 2023.11.15 타게팅 대상지정까지 완료
	void Toggle_Target();
	void BeginTarget();
	void EndTarget();
	void ChangeTarget(ACharacter* target);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	TWeakObjectPtr<class ACharacter> OwnerCharacter;
	TWeakObjectPtr<class ACharacter> Target;
	TArray<FHitResult> HitResults;
	class UFXSystemComponent* ParticleComponent;


public:
	UPROPERTY(EditAnywhere)
		float TargettingRange = 1000.0f;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditAnywhere)
		class UFXSystemAsset* Particle;
};
