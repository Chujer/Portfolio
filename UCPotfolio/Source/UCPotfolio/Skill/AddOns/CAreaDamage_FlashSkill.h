#pragma once

#include "CoreMinimal.h"
#include "Skill/AddOns/CAreaDamage.h"
#include "CAreaDamage_FlashSkill.generated.h"

UCLASS()
class UCPOTFOLIO_API ACAreaDamage_FlashSkill : public ACAreaDamage
{
	GENERATED_BODY()

public:
	ACAreaDamage_FlashSkill();
public:
	virtual void BeginPlay() override;
	virtual void BeginPlay(ACharacter* InCharacter) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;

protected:
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	UPROPERTY(EditAnywhere)
		float UpScale = 1250;

	FVector EndLocation;
	FTransform StartTrasnform;

private:
	TArray<AActor*> TargetActors;

};
