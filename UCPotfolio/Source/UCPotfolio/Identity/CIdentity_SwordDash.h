#pragma once

#include "CoreMinimal.h"
#include "Identity/CIdentity.h"
#include "CIdentity_SwordDash.generated.h"

UCLASS()
class UCPOTFOLIO_API UCIdentity_SwordDash : public UCIdentity
{
	GENERATED_BODY()

public:
	UCIdentity_SwordDash();

	virtual void BeginPlay(ACAttachment* InAttachment, ACharacter* InCharacter) override;
	virtual void DoIdentity() override;

public:
	UFUNCTION()
		void DashTimeLine(float Output);

private:
	UPROPERTY(EditAnywhere)
		UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float DashRange = 1300;

	UPROPERTY(EditAnywhere)
		FVector CollisionRange = FVector(30, 30, 60);

	UPROPERTY(EditAnywhere)
		UCurveFloat* NormalCurve;
private:
	float a = 0;
	FVector EndPoint;
};
