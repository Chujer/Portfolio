#include "Global.h"
#include "Skill/CSkill_Nomal.h"
#include "Components/CStateComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Character.h"
#include "Characters/CPlayer.h"
#include "Characters/ICharacter.h"
#include "Weapon/CAttachment.h"
#include "Skill/AddOns/CGhostTrail.h"
#include "Skill/Sword/CHaveAction_GhostSlash.h"

class IICharacter;

void UCHaveAction_GhostSlash::Pressed()
{
	CheckFalse(StateComponent.Get()->IsIdleMode());

	Super::Pressed();

	PlayMontage();
	Attachment->OnAttachmentEndCollision.AddUniqueDynamic(this, &UCHaveAction_GhostSlash::OnAttachmentEndCollision);
	Attachment->OnAttachmentBeginOverlap.AddUniqueDynamic(this, &UCHaveAction_GhostSlash::OnAttachmentBeginOverlap);
	
}

void UCHaveAction_GhostSlash::Released()
{
	bPressed = false;
}

void UCHaveAction_GhostSlash::End_Skill_Implementation()
{
	Super::End_Skill_Implementation();

	Attachment->OnAttachmentBeginOverlap.Remove(this, "OnAttachmentBeginOverlap");
	Attachment->OnAttachmentEndCollision.Remove(this, "OnAttachmentEndCollision");
}

void UCHaveAction_GhostSlash::SkillAction1()
{
	Super::SkillAction1();
	ACGhostTrail* ghostTrail = CHelpers::Play_GhostTrial(GhostTrail, Character.Get());
	GhostTrails.Add(ghostTrail);
	ghostTrail->EndTimer();
}

void UCHaveAction_GhostSlash::SkillAction2()
{
	Super::SkillAction2();
	ACGhostTrail* stopGhost = CHelpers::Play_GhostTrial(StopGhostClass, Character.Get());
	ACGhostTrail* ghostTrail = CHelpers::Play_GhostTrial(GhostTrail, Character.Get());
	stopGhost->EndTimer();
	stopGhost->SetOriginMaterial();
	GhostTrails.Add(ghostTrail);
	GhostTrails.Add(stopGhost);
}

void UCHaveAction_GhostSlash::EndSkillAction1()
{
	Super::EndSkillAction1();

	CheckTrue(GhostTrails.Num() < 1);

	for(int i = GhostTrails.Num()-1; i >=0;i--)
	{
		GhostTrails[i]->Destroy();
	}
}

void UCHaveAction_GhostSlash::OnAttachmentEndCollision()
{
	Super::OnAttachmentEndCollision();

	Hitted.Empty();
}

void UCHaveAction_GhostSlash::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCuaser, ACharacter* InOther)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCuaser, InOther);

	CheckNull(InOther);


	for (ACharacter* hitted : Hitted)
	{
		CheckTrue(hitted == InOther);
	}

	Hitted.AddUnique(InOther);
	//공격 판정
	IICharacter* HitActor;
	HitActor = Cast<IICharacter>(InOther);
	HitActor->ApplyDamage(InAttacker, InAttackCuaser, *DamageType, SkillData.Power);
	HitActor->LaunchTarget(InOther, SkillData.Launch);
}