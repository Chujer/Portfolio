#include "Skill/CHaveAction_CreateProjectile.h"
#include "Global.h"
#include "AddOns/CAddon_Projectile.h"
#include "Characters/CPlayer.h"
#include "Characters/ICharacter.h"
#include "GameFramework/Character.h"
#include "Weapon/CAttachment.h"

void UCHaveAction_CreateProjectile::Pressed()
{
	Super::Pressed(); 
	PlayMontage();
}

void UCHaveAction_CreateProjectile::SkillAction1()
{
	Super::SkillAction1();

	FTransform transform;
	transform.SetLocation(Attachment.Get()->GetActorLocation());
	transform.SetRotation(FQuat(Character.Get()->GetActorRotation()));

	ProjectilActor = Character.Get()->GetWorld()->SpawnActor<ACAddon_Projectile>(ProjectileClass, transform);
	ProjectilActor->OnBeginOverlapEnemy.AddDynamic(this, &UCHaveAction_CreateProjectile::BeginOverlap);
}

void UCHaveAction_CreateProjectile::BeginOverlap(ACharacter* InOtherCharacter, EDamageType InDamageType)
{
	IICharacter* iCharacter = Cast<IICharacter>(InOtherCharacter);

	CheckNull(iCharacter);

	iCharacter->ApplyDamage(Cast<ACharacter>(Character), Cast<AActor>(Attachment), InDamageType, SkillData.Power);
}
