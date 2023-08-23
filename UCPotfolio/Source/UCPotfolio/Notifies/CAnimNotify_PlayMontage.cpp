#include "Notifies/CAnimNotify_PlayMontage.h"

#include "Global.h"


FString UCAnimNotify_PlayMontage::GetNotifyName_Implementation() const
{
	return "PlayAnimMontage";
}

void UCAnimNotify_PlayMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	ACharacter* ownerCharacter = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(ownerCharacter);
	ownerCharacter->PlayAnimMontage(AnimMontage);
}
