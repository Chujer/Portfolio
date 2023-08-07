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
	virtual void BeginPlay(ACAttachment* InAttachment, ACharacter* InCharacter);

protected:
	class ACharacter* OwnerCharacter;
	class ACAttachment* Attachment;

protected:
	bool bActiveIdentity;

};
