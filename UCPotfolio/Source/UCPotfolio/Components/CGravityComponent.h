#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGravityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartZeroGravity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndZeroGravity);
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
	void ResetGravityTime();

public:
	UFUNCTION()
	void OnLanded(const FHitResult& Hit);

public:
	FORCEINLINE bool IsZeroGravity() { return bZeroGravity; }

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnStartZeroGravity OnStartZeroGravity;
	FOnEndZeroGravity OnEndZeroGravity;

private:
	class ACharacter* Character;
	class UCharacterMovementComponent* CharacterMovementComponent;
	bool bZeroGravity = false;

	UPROPERTY(EditAnywhere, Category = "ZeroGravity")
		float ZeroGravityTime = 0.8f;
	float GravityTime = 0;
};
