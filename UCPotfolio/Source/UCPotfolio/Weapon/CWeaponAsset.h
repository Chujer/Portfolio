#pragma once

#include "CoreMinimal.h"
#include "CAttachment.h"
#include "Engine/DataAsset.h"
#include "CWeaponStructures.h"
#include "CWeaponAsset.generated.h"



UCLASS()
class UCPOTFOLIO_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE class ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class UCDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class UCDoAction* GetDoAirAction() { return DoAirAction; }
	FORCEINLINE class UCDoAction* GetDoNormalAction() { return DoNormalAction; }

public:
	void SetDoAirAction();
	void SetDoNormalAction(); 

public:
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner);

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCDoAction> DoActionClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCDoAction> DoAirActionClass;

	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> DoAirActionDatas;
private:
	UPROPERTY()
		class ACAttachment* Attachment;

	UPROPERTY()
		class UCDoAction* DoAction;

	UPROPERTY()
		class UCDoAction* DoNormalAction;

	UPROPERTY()
		class UCDoAction* DoAirAction;
};
