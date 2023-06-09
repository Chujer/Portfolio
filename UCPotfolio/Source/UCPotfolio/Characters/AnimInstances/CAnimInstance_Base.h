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

protected:
	class ACharacter* OwnerCharacter;

private:
	FRotator PrevRotation;
};
