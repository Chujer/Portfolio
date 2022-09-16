#include "Framework.h"
#include "Character.h"

Character::Character(Vector3 position, Vector3 size)
{
	animRect = new AnimationRect(position, size);
	animator = new Animator();
	sb = new ShadedBuffer();
}

Character::~Character()
{
	SAFE_DELETE(animator);
	SAFE_DELETE(animRect);
	SAFE_DELETE(sb);
}
