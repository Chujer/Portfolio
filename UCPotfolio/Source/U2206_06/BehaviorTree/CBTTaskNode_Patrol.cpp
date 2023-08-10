#include "BehaviorTree/CBTTaskNode_Patrol.h"
#include "Global.h"
#include "CPatrolPath.h"
#include "Components/SplineComponent.h"
#include "Components/CAIBehaviorComponent.h"
#include "Characters/CEnemy_AI.h"
#include "Characters//CAIController.h"
#include "NavigationSystem.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";

	//태스크에서는 노티파이 틱을 켜주지 않으면 틱이 동작하지 않음
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCAIBehaviorComponent* behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	GLog->Log(ai->GetActorLabel());
	GLog->Logf(L"%p", this);
	//CLog::Print(ai->GetPatrolPath()->GetName());

	if (!!ai->GetPatrolPath())
	{
		FVector moveToPoint = ai->GetPatrolPath()->GetMoveTo();
		behavior->SetPatrolLocation(ai->GetPatrolPath()->GetMoveTo());
		//Location = ai->GetPatrolPath()->GetMoveTo();
		if (bDebugMode)
			DrawDebugSphere(ai->GetWorld(), moveToPoint, 10, 10, FColor::Green, true, 5);
		return EBTNodeResult::InProgress;
	}

	FVector location = ai->GetActorLocation();

	UNavigationSystemV1* navSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(ai->GetWorld());
	CheckNullResult(navSystem, EBTNodeResult::Failed);
	
	FNavLocation point(location);   
	if (navSystem->GetRandomPointInNavigableRadius(location, Distance, point))
	{
		behavior->SetPatrolLocation(point.Location);

		if (bDebugMode)
			DrawDebugSphere(ai->GetWorld(), location, 25, 25, FColor::Green, true, 5);

		return EBTNodeResult::InProgress;   //아직 끝나지 않았다
	}

	return EBTNodeResult::Failed;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCAIBehaviorComponent* behavior = CHelpers::GetComponent<UCAIBehaviorComponent>(ai);

	FVector location = behavior->GetPatrolLocation();

	EPathFollowingRequestResult::Type result = controller->MoveToLocation(location, 5, false);

	switch (result)
	{
		case EPathFollowingRequestResult::Failed:
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			break;

		case EPathFollowingRequestResult::AlreadyAtGoal:
		{
			if (ai->GetPatrolPath())
				ai->GetPatrolPath()->UpdateIndex();

;
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			break;
		}
	}
}