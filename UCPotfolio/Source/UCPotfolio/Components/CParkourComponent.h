#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CParkourComponent.generated.h"

UENUM(BlueprintType)
enum class EParkourArrowType : uint8
{
	Center = 0, Ceil, Floor, Left, Right, Land, Max,
};

UENUM(BlueprintType)
enum class EParkourType : uint8
{
	Climb = 0, Fall, Slide, Short, Normal, Wall, Max,
};

//���� ���� ������
USTRUCT(BlueprintType)
struct FParkourData : public FTableRowBase
{
	GENERATED_BODY()

public:
	void PlayMontage(class ACharacter* InCharacter);

public:
	UPROPERTY(EditAnywhere)
		EParkourType Type;

	UPROPERTY(EditAnywhere)
		UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRatio = 1;

	UPROPERTY(EditAnywhere)
		FName SectionName;

	UPROPERTY(EditAnywhere)
		float MinDistance;

	UPROPERTY(EditAnywhere)
		float MaxDistance;

	UPROPERTY(EditAnywhere)
		float Extent;

	UPROPERTY(EditAnywhere)
		bool bFixedCamera;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCPOTFOLIO_API UCParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCParkourComponent();

public:
	FORCEINLINE bool IsExecuting() { return Type != EParkourType::Max; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void LineTrace(EParkourArrowType InType);
	void CheckTrace_Center();
	void CheckTrace_Ceil();
	void CheckTrace_Floor();
	void CheckTrace_LeftRight();
	void CheckTrace_Land();

private:
	bool Check_Obstacle();

public:
	void DoParkour(bool bLanded);
	void End_DoParkour();

private:
	bool Check_ClimbMode();
	void DoParkour_Climb();
	void End_DoParkour_Climb();

private:
	bool Check_FallMode();
	void DoParkour_Fall();
	void End_DoParkour_Fall();

private:
	bool Check_ObstacleMode(EParkourType InType, FParkourData& OutData);
	void DoParkour_Obstacle(EParkourType InType, FParkourData& InData);
	void End_DoParkour_Obstacle();

private:
	bool Check_SlideMode();
	void DoParkour_Slide();
	void End_DoParkour_Slide();

private:
	UPROPERTY(EditAnywhere, Category = "Data")
		UDataTable* DataTable;

private:
	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceDistance = 600;

	UPROPERTY(EditAnywhere, Category = "Trace")
		TEnumAsByte<EDrawDebugTrace::Type> DebugType;


	UPROPERTY(EditAnywhere, Category = "Trace")
		float AvailableFrontAngle = 15;

private:
	class ACharacter* OwnerCharacter;
	class UArrowComponent* Arrows[(int32)EParkourArrowType::Max];

	FHitResult HitResults[(int32)EParkourArrowType::Max];

	AActor* HitObstacle;
	FVector HitObstacleExtent;
	float HitDistance;
	float ToFrontYaw;

private:
	EParkourType Type = EParkourType::Max;

private:
	TMap<EParkourType, TArray<FParkourData>> DataMap;

private:
	bool bFalling;

private:
	AActor* BackupObstacle;
};
