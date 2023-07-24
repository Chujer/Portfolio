#include "Parkour/CAnimNotify_Parkour.h"

#include "Global.h"
#include "CParkourComponent.h"

FString UCAnimNotify_Parkour::GetNotifyName_Implementation() const
{
	return "Parkour";
}

void UCAnimNotify_Parkour::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCParkourComponent* parkour = CHelpers::GetComponent<UCParkourComponent>(MeshComp->GetOwner());
	CheckNull(parkour);

	parkour->End_DoParkour();
}