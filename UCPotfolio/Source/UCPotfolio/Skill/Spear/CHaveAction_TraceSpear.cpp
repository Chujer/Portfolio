#include "Skill/Spear/CHaveAction_TraceSpear.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Skill/AddOns/CTraceSpear.h"
#include "Weapon/CAttachment.h"

void UCHaveAction_TraceSpear::Pressed()
{
	Super::Pressed();

	PlayMontage();
	SkillAction1();	//TODO::2023.10.24 - 생성 테스트 
}

void UCHaveAction_TraceSpear::BeginPlay(ACPlayer* InCharacter, ACAttachment* InAttachment)
{
	Super::BeginPlay(InCharacter, InAttachment);
}

void UCHaveAction_TraceSpear::SkillAction1()
{
	Super::SkillAction1();
	
	FActorSpawnParameters params;
	params.Name = "TraceSpear";
	params.Owner = Attachment.Get();

	TraceSpear = Cast<ACTraceSpear>(Character->GetWorld()->SpawnActor<ACTraceSpear>(TraceSpear->StaticClass(), Attachment->GetActorTransform(),params));
}
