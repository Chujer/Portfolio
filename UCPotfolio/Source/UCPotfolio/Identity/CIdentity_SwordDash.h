#pragma once

#include "CoreMinimal.h"
#include "Characters/ICharacter.h"
#include "Components/TimelineComponent.h"
#include "Identity/CIdentity.h"
#include "CIdentity_SwordDash.generated.h"

UCLASS(Blueprintable)
class UCPOTFOLIO_API UCIdentity_SwordDash : public UCIdentity
{
	GENERATED_BODY()

public:
	UCIdentity_SwordDash();

	virtual void BeginPlay(ACAttachment* InAttachment, ACharacter* InCharacter) override;
	virtual void DoIdentityMontage() override;
	virtual void DoIdentity() override;
	virtual void Tick(float InDeltaTime) override;

public:
	UFUNCTION()
		void DashTimeLine(float time);

protected:
	UPROPERTY(EditAnywhere)
		UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float DashRange = 1300;

	UPROPERTY(EditAnywhere)
		FVector CollisionRange = FVector(30, 30, 60);

	UPROPERTY(EditAnywhere)
		UCurveFloat* NormalCurve;

private:
	IICharacter* Target;
	FVector MovePos;
	FVector EndPoint;
	FTimeline Timeline;
};
