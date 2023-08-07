#include "Identity/CIdentity.h"
#include "Weapon/CAttachment.h"

void UCIdentity::BeginPlay(ACAttachment* InAttachment, ACharacter* InCharacter)
{
	Attachment = InAttachment;
	OwnerCharacter = InCharacter;
}
