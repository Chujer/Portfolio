#include "Weapon/CDoAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"

UCDoAction::UCDoAction()
{
}

void UCDoAction::BeginPlay(ACharacter* InOwner, const TArray<FDoActionData>& InDoActionDatas)
{
	OwnerCharacter = InOwner;

	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Movement = CHelpers::GetComponent<UCMovementComponent>(OwnerCharacter);

	DoActionDatas = InDoActionDatas;
}

void UCDoAction::DoAction()
{
	bInAction = true;
	State->SetActionMode();
}

void UCDoAction::Begin_DoAction()
{
	bInAction = true;
}

void UCDoAction::End_DoAction()
{
	bInAction = false;

	State->SetIdleMode();

	Movement->Move();
	Movement->DisableFixedCamera();
}

void UCDoAction::OnAttachmentEndCollision()
{
	CheckTrue(State->IsSkillMode());
}

void UCDoAction::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	CheckTrue(State->IsSkillMode());
}
