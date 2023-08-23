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
		void SetDownDirection(float InDownDirection);
public:
	void ResetDownTime();
protected:
	class ACCharacter_Base* OwnerCharacter;

	float MaxDownTime = 1.5f;
	FRotator PrevRotation;
	float DownTime = 0;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bDown = false;

	UPROPERTY(BlueprintReadOnly)
		float DownDirection = 0;

	UPROPERTY(BlueprintReadOnly)
		bool bFalling = false;

private:
	class UAnimMontage* FrontWakeupMontage;
	class UAnimMontage* BackWakeupMontage;
};
