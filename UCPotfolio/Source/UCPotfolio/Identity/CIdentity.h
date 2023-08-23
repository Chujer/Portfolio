#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CIdentity.generated.h"

class ACAttachment;
UCLASS()
class UCPOTFOLIO_API UCIdentity : public UObject
{
	GENERATED_BODY()

public:
	virtual void DoIdentity() {}
	virtual void DoIdentityMontage(){}
	virtual void BeginPlay(ACAttachment* InAttachment, ACharacter* InCharacter);

public:
	virtual void Tick(float InDeltaTime) {}

protected:
	class ACharacter* OwnerCharacter;
	class ACAttachment* Attachment;

protected:
	bool bActiveIdentity;

};
