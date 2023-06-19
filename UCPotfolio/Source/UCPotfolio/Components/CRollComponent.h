#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRollComponent.generated.h"

UENUM()
enum class ERollDirection : uint8
{
	Front = 0, Back, Left, Right, MAX,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPOTFOLIO_API UCRollComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCRollComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void Roll();

private:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* RollMontage[ERollDirection::MAX];

private:
	class ACharacter* OwnerCharacter;
	ERollDirection EDirection;
};
