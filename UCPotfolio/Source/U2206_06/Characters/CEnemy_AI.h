#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "Components/WidgetComponent.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class U2206_06_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		uint8 TeamID = 2;

private:
	UPROPERTY(EditInstanceOnly, Category = "AI")
		TSoftObjectPtr<class ACPatrolPath> PatrolPath;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Label")
		float LabelViewAmount = 3000.0f;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* LabelWidget;

private:


protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCWeaponComponent* Weapon;

	UPROPERTY(VisibleDefaultsOnly)
		class UCAIBehaviorComponent* Behavior;

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE class ACPatrolPath* GetPatrolPath() { return PatrolPath.Get(); }

public:
	ACEnemy_AI();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	void UpdateLabelRenderScale();
};
