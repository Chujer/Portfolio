#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill.h"
#include "CSkill_HaveAction.generated.h"


UCLASS()
class UCPOTFOLIO_API UCSkill_HaveAction : public UCSkill
{
	GENERATED_BODY()

public:
	void SelectSkillAction(int Index);

	virtual void SkillAction1() {}
	virtual void SkillAction2() {}
	virtual void SkillAction3() {}
	virtual void SkillAction4() {}

	virtual void EndSkillAction1() {}
	virtual void EndSkillAction2() {}
	virtual void EndSkillAction3() {}
	virtual void EndSkillAction4() {}

public:
	virtual void EndSkillAction(int Index);
	virtual void Cansle();

};
