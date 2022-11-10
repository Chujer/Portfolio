#include "Framework.h"
#include "Coroutine.h"

void Coroutine::Update()
{
	if (onCoroutine == true)
	{
		coroutineTime += Time::Delta();
	}
}
