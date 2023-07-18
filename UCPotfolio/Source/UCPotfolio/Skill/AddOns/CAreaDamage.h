#pragma once

#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "Components/ShapeComponent.h"
#include "CAreaDamage.generated.h"

UCLASS()
class UCPOTFOLIO_API ACAreaDamage : public AActor
{
	GENERATED_BODY()

public:
	ACAreaDamage();

public:
	virtual void BeginPlay() override;
	virtual void BeginPlay(class ACharacter* InCharacter);

	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION()
		virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){};


protected:
	class ACharacter* Character;
	class ACAttachment* Attachment;
	TArray<AActor*> Ignores;
	UPROPERTY(EditAnywhere)
		UShapeComponent* MainCollision;
};
