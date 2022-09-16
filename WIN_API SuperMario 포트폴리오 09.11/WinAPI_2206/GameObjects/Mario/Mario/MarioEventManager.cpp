#include "Framework.h"

MarioEventManager::MarioEventManager()
{
}

MarioEventManager::~MarioEventManager()
{
}

void MarioEventManager::AddEvent(string key, function<void()> Event)
{
	Events[key] = Event;
}
