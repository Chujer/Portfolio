#include "Skill/CSkill_HaveAction.h"
#include "Global.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Utilities/CLog.h"
#include "Weapon/CAttachment.h"


void UCSkill_HaveAction::SelectSkillAction(int Index)
{
	switch (Index)
	{
		case 1:
			SkillAction1();
			break;
		case 2:
			SkillAction2();
			break;
		case 3:
			SkillAction3();
			break;
		case 4:
			SkillAction4();
			break;
	default:
		CLog::Print("CSkill_HaveAction Index Error : SkillAction");
		break;
	}
}

void UCSkill_HaveAction::EndSkillAction(int Index)
{
	switch (Index)
	{
	case 1:
		EndSkillAction1();
		break;
	case 2:
		EndSkillAction2();
		break;
	case 3:
		EndSkillAction3();
		break;
	case 4:
		EndSkillAction4();
		break;
	default:
		CLog::Print("CSkill_HaveAction Index Error : EndSkill");
		break;
	}
}

void UCSkill_HaveAction::Cansle()
{
	EndSkillAction1();
	EndSkillAction2();
	EndSkillAction3();
	EndSkillAction4();
	End_Skill_Implementation();
	Attachment->ClearCurrentSkill();
}
