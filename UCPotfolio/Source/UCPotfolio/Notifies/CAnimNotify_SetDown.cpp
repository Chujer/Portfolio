#include "Notifies/CAnimNotify_SetDown.h"
#include "Global.h"
#include "Characters/AnimInstances/CAnimInstance_Base.h"

FString UCAnimNotify_SetDown::GetNotifyName_Implementation() const
{
	return "SetDown";
}

void UCAnimNotify_SetDown::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//TODO : animation으로 캐스팅이 안됨
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetAnimInstance());
	Super::Notify(MeshComp, Animation);
	UAnimInstance* anim = MeshComp->GetAnimInstance();

	UCAnimInstance_Base* animation = Cast<UCAnimInstance_Base>(anim);
	CheckNull(animation);
	animation->SetAnimDown(DownDirection);
}
