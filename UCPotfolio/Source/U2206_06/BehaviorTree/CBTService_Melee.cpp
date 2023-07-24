#include "BehaviorTree/CBTService_Melee.h"
#include "Global.h"
//#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CAIBehaviorComponent.h"
#include "Components/CAIController.h"
#include "BehaviorTree/CPatrolPath.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";

	Interval = 0.1f;	//0.1�ʸ��� ��
	RandomDeviation = 0;	//�� �ֱ� ������ 0
	
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
	UCAIBehaviorComponent* aiState = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	if(state->IsHittedMode())
	{
		aiState->SetHittedMode();
		
		return;
	}

	ACharacter* character = aiState->GetTarget();
	if(character == nullptr)
	{
		aiState->SetPatrolMode();

		return;
	}

	float distance = ai->GetDistanceTo(character);
	if(distance < ActionRange)
	{
		aiState->SetActionMode();

		return;
	}

	aiState->SetApproachMode();
}
