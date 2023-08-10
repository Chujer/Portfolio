#pragma once

#include "CoreMinimal.h"
#include "Weapons/CAttachment.h"
#include "CAttachment_Bow.generated.h"

UCLASS()
class U2206_06_API ACAttachment_Bow : public ACAttachment
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "View")
		FVector2D ViewPitchRange = FVector2D(-40, +30);

private:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* SkeletaMesh;

	UPROPERTY(VisibleAnywhere)
		class UPoseableMeshComponent* PoseableMesh;

public:
	float* GetBend();

public:
	ACAttachment_Bow();

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnBeginEquip_Implementation() override;
	virtual void OnUnEquip_Implementation() override;

private:
	FVector2D OriginViewPitchRange;
};
