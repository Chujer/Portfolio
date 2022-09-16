#pragma once

#include "Geomatries/AnimationRect.h"
#include "Utilities/Animator.h"

enum State
{
	INTRO = 0,
	INTRO2 = 1,
	IDLE = 2,
	ATTACK = 3,
	ATTACK2 = 4,
	ATTACK2R = 5,
	DEATH = 6,
	DEATH_LEAVE = 7,
	ATTACK_READY = 8,
	ATTACK_LOOP = 9,
	ATTACK_END = 10,
	ATTACK_ON = 11
};

class ShadedBuffer : public ShaderBuffer
{
public:
	ShadedBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.selection = 0;
	}
	void SetPoint(int selection) { data.selection = selection; }
	int* GetSelectionPtr() { return &data.selection; }

	struct Data
	{
		int selection;
		Vector3 i;
	};

private:
	Data data;
};
class Character
{
public:
	Character(Vector3 position, Vector3 size);
	virtual ~Character();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Move() = 0;
	virtual bool GetActive() = 0;
	virtual void SetActive(bool active) = 0;
	AnimationRect* GetAnimRect(){ return animRect; }
protected:
	Animator* animator = nullptr;
	AnimationRect* animRect = nullptr;
	string Tag = "NULL";
	class ShadedBuffer* sb = nullptr;
};