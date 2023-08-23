#include "Skill/Spear/CHaveAction_DragonSpear.h"
#include "Skill/AddOns/CSpeare_Pull.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "NiagaraSystem.h"
#include "Characters/ICharacter.h"

void UCHaveAction_DragonSpear::Pressed()
{
	Super::Pressed();

	PlayMontage();
}

void UCHaveAction_DragonSpear::SkillAction1()
{
	Super::SkillAction1();

	FTransform transform = Character->GetActorTransform();

	FActorSpawnParameters params;
	params.Owner = Character.Get();
	PullAddOn = Cast<ACSpeare_Pull>(Character->GetWorld()->SpawnActor(PullAddOnClass,&transform, params));

	Smoke = Cast<UNiagaraComponent>(CHelpers::PlayEffect(Character->GetWorld(), SmokeNiagara, Character->GetActorTransform()));
}

void UCHaveAction_DragonSpear::SkillAction2()
{
	Super::SkillAction2();

	Character->SetActorHiddenInGame(true);
	TArray<AActor*> childs;
	childs = Character->Children;
	for (AActor* child : childs)
		child->SetActorHiddenInGame(true);
	Character->GetWorld()->SpawnActor(DragonActor, &(Character->GetTransform()));
}

void UCHaveAction_DragonSpear::SkillAction3()
{
	Super::SkillAction3();
	CLog::Log("SkillAction3");
	Smoke->SetActive(false);

	//�ٴ� ������ ����Ʈ ��ġ ����
	FVector EndAttackOffset = FVector::ZeroVector;
	EndAttackOffset.Z = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FTransform transform = Character->GetActorTransform();
	transform.SetLocation(Character->GetActorLocation() - EndAttackOffset);

	CHelpers::PlayEffect(Character->GetWorld(), AttackEndNiagara, transform);

	//����ȭ��Ų ĳ����, ����� Ȱ��ȭ
	Character->SetActorHiddenInGame(false);
	TArray<AActor*> childs;
	childs = Character->Children;
	for (AActor* child : childs) 
		child->SetActorHiddenInGame(false);

	for (ACharacter* target : PullAddOn->GetTargets())
	{
		IICharacter* iCharacter = Cast<IICharacter>(target);
		iCharacter->ApplyDamage(Character.Get(), Cast<AActor>(Attachment), DamageType, Power);
		target->CustomTimeDilation = 1.0f;
		target->GetCapsuleComponent()->SetCollisionProfileName("Enemy");
	}
	PullAddOn->Destroy();
}

