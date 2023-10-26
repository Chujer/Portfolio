#include "Skill/Spear/CHaveAction_TraceSpear.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Skill/AddOns/CTraceSpear.h"
#include "Weapon/CAttachment.h"

void UCHaveAction_TraceSpear::Pressed()
{
	Super::Pressed();

	PlayMontage();
	SkillAction1();
}

void UCHaveAction_TraceSpear::BeginPlay(ACPlayer* InCharacter, ACAttachment* InAttachment)
{
	Super::BeginPlay(InCharacter, InAttachment);
}

void UCHaveAction_TraceSpear::SkillAction1()
{
	Super::SkillAction1();

	CheckNull(TraceSpearClass);

	FActorSpawnParameters params;
	FActorSpawnParameters params2;
	params.Owner = Attachment.Get();

	
	TraceSpear = Character->GetWorld()->SpawnActor<ACTraceSpear>(TraceSpearClass, Attachment->GetActorTransform(),params);
}


