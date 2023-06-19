#include "Characters/ICharacter.h"
#include "GameFramework/Character.h"

void IICharacter::Change_Color(ACharacter* InCharacter, FLinearColor InColor)
{
	for (UMaterialInterface* material : InCharacter->GetMesh()->GetMaterials())
	{
		UMaterialInstanceDynamic* instance = Cast<UMaterialInstanceDynamic>(material);
		if (!!instance)
			instance->SetVectorParameterValue("BodyColor", InColor);
	}
}
