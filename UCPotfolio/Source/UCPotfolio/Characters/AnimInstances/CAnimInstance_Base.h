#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Base.generated.h"

UCLASS()
class UCPOTFOLIO_API UCAnimInstance_Base : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		float Pitch;

	UPROPERTY(BlueprintReadOnly, Category = "Animation")
		float Direction;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
		void SetFrontWakeupMontage(UAnimMontage* InMontage);

	UFUNCTION(BlueprintCallable)
		void SetBackWakeupMontage(UAnimMontage* InMontage);

	UFUNCTION(BlueprintCallable)
		void SetAnimDown(float InDownDirection);
protected:
	class ACharacter* OwnerCharacter;

private:
	FRotator PrevRotation;

	float MaxDownTime = 2.0f;
	float DownTime = 0;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bDown = false;
	UPROPERTY(BlueprintReadOnly)
	float DownDirection = 0;
private:
	class UAnimMontage* FrontWakeupMontage;
	class UAnimMontage* BackWakeupMontage;
};
