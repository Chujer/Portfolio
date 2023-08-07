#include "Notifies/CAnimNotify_EndParkour.h"
#include "Global.h"
#include "Components/CParkourComponent.h"

FString UCAnimNotify_EndParkour::GetNotifyName_Implementation() const
{
	return "EndParkour";
}

void UCAnimNotify_EndParkour::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCParkourComponent* parkourComponent = CHelpers::GetComponent<UCParkourComponent>(MeshComp->GetOwner());
	CheckNull(parkourComponent);

	parkourComponent->End_DoParkour();
}
