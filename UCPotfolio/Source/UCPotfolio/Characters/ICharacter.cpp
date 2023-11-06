#include "Characters/ICharacter.h"
#include "GameFramework/Character.h"
#include "Global.h"

void IICharacter::Change_Color(ACharacter* InCharacter, FLinearColor InColor)
{
	for (UMaterialInterface* material : InCharacter->GetMesh()->GetMaterials())
	{
		UMaterialInstanceDynamic* instance = Cast<UMaterialInstanceDynamic>(material);
		if (!!instance)
			instance->SetVectorParameterValue("BodyColor", InColor);
	}
}

void IICharacter::LaunchTarget(ACharacter* InTarget, FVector InLaunchVelocity)
{
	CheckNull(InTarget);

	InLaunchVelocity = (InTarget->GetActorForwardVector() * -1) * InLaunchVelocity.X;

	InTarget->LaunchCharacter(InLaunchVelocity, true, true);
}
