#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CWeaponStructures.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class U2206_06_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCEquipment> EquipmentClass;
	
	UPROPERTY(EditAnywhere)
		FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCDoAction> DoActionClass;

	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

	UPROPERTY(EditAnywhere)
		TArray<FHitData> HitDatas;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCSubAction> SubActionClass;

public:
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutWeaponData);




#if WITH_EDITOR
	/*
	UDataAsset::PostEditChangeChainProperty : 프로퍼티 배열의 변경점이 있을때 호출
	UDataAsset::PostEditChangeProperty : 프로퍼티가 변경됐을때 호출
	*/
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;	
#endif
	//WITH_EDITOR
};
