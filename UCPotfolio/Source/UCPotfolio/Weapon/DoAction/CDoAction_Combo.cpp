#include "Weapon/DoAction/CDoAction_Combo.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"

UCDoAction_Combo::UCDoAction_Combo()
{
}

void UCDoAction_Combo::DoAction()
{
	CheckTrue(DoActionDatas.Num() < 1)

	if(bEnable)
	{
		bEnable = false;
		bExist = true;

		return;
	}

	CheckFalse(State->IsIdleMode());
	
	Super::DoAction();
	DoActionDatas[Index].PlayDoAction(OwnerCharacter);
}

void UCDoAction_Combo::Begin_DoAction()
{
	Super::Begin_DoAction();
	CheckFalse(bExist);

	bExist = false;
	DoActionDatas[++Index].PlayDoAction(OwnerCharacter);
}

void UCDoAction_Combo::End_DoAction()
{
	Super::End_DoAction();

	Index = 0;
}
