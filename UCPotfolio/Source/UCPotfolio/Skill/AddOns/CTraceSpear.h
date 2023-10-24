#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "CTraceSpear.generated.h"

UCLASS()
class UCPOTFOLIO_API ACTraceSpear : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTraceSpear();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "MeshComponent")
		class UStaticMeshComponent* SM_Spear;

	UPROPERTY(EditAnywhere, Category = "Effect")
		TArray<UFXSystemAsset*> SpearEffect;

private:
	UPROPERTY()
		class USceneComponent* root;
};
