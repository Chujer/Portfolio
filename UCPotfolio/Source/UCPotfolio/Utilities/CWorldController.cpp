#include "Utilities/CWorldController.h"


#include "CHelpers.h"
#include "CLog.h"

void CWorldController::PlayStopWorld(UWorld* InWorld, float StopTime)
{
	CheckTrue(FMath::IsNearlyZero(StopTime));

	TArray<APawn*> pawns;
	for(AActor* actor : InWorld->GetCurrentLevel()->Actors)
	{
		APawn* pawn = Cast<APawn>(actor);

		if(!!pawn)
		{
			pawn->CustomTimeDilation = 1e-3f;
			pawns.Add(pawn);
		}
	}

	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([=]()
	{
		for(APawn* pawn : pawns)
		{
			pawn->CustomTimeDilation = 1.0f;
		}
	});
	FTimerHandle TimerHandle;
	InWorld->GetTimerManager().SetTimer(TimerHandle, timerDelegate, StopTime, false);
}
