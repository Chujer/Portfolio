#include "UCPotfolioGameModeBase.h"
#include "Utilities/CHelpers.h"

AUCPotfolioGameModeBase::AUCPotfolioGameModeBase()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");
}
 