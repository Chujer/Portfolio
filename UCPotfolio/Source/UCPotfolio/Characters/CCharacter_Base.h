#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter_Base.generated.h"

UCLASS(Abstract)
class UCPOTFOLIO_API ACCharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ACCharacter_Base();

protected:
	virtual void BeginPlay() override;
	void SetMesh(FString InPath);


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;


	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

};
