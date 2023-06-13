#pragma once

#include "CoreMinimal.h"
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

public:
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner);



private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCDoAction> DoActionClass;
	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

		
private:
	UPROPERTY()
		class ACAttachment* Attachment;

	UPROPERTY()
		class UCDoAction* DoAction;
};
