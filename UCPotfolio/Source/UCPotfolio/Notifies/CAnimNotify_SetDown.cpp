#include "Notifies/CAnimNotify_SetDown.h"
#include "Global.h"
#include "Characters/CCharacter_Base.h"
#include "Characters/AnimInstances/CAnimInstance_Base.h"

FString UCAnimNotify_SetDown::GetNotifyName_Implementation() const
{
	return "SetDown";
}

void UCAnimNotify_SetDown::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//TODO : animation으로 캐스팅이 안됨
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp->GetAnimInstance());
	UCAnimInstance_Base* anim = Cast<UCAnimInstance_Base>(MeshComp->GetAnimInstance());
	CheckNull(anim);
	anim->SetDownDirection(DownDirection);
}
