#include "Framework.h"
#include "EventTile.h"

EventTile::EventTile()
{
}

EventTile::~EventTile()
{
}

void EventTile::SetEvent(string name)
{
	if (name == "FlagBar" || name == "Flag" || name == "C_Pipe005" || name == "C_Pipe006")
	{
		Event = bind(&MarioGameManager::StageClear,MarioGameManager::Get());
	}
}

