#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "CSkillObject.generated.h"

UCLASS(Abstract)
class UCPOTFOLIO_API ACSkillObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSkillObject();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Spawn() {};

public:	
	virtual void Tick(float DeltaTime) override;

public:
	ACharacter* OwnerCharacter;
};
