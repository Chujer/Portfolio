#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGravityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartGravity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndGravity);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPOTFOLIO_API UCGravityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCGravityComponent();

protected:
	virtual void BeginPlay() override;

public:
	void StartZeroGravity();
	void EndZeroGravity();

public:
	FORCEINLINE void ResetGravityTime() { GravityTime = 0; }

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnStartGravity OnStartGravity;
	FOnEndGravity OnEndGravity;

private:
	class ACharacter* Character;
	class UCharacterMovementComponent* CharacterMovementComponent;
	bool bZeroGravity = false;

	UPROPERTY(EditAnywhere, Category = "ZeroGravity")
		float ZeroGravityTime = 0.8f;
	float GravityTime = 0;
};
