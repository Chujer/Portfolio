#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	void Roll();


private:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* RollMontage[ERollDirection::MAX];

private:
	TWeakObjectPtr<class ACharacter> OwnerCharacter;
	ERollDirection EDirection;
};
