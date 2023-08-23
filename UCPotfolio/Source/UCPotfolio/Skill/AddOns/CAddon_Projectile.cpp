#include "Skill/AddOns/CAddon_Projectile.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Components/BoxComponent.h"

ACAddon_Projectile::ACAddon_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box");
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &ProjectileComponent, "ProjectileComponent");

	ProjectileComponent->ProjectileGravityScale = 0;
	Box->BodyInstance.bNotifyRigidBodyCollision = true;
	Box->SetCollisionProfileName("OverlapAll");
}

void ACAddon_Projectile::BeginPlay()
{
	Super::BeginPlay();

	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACAddon_Projectile::OnComponentBeginOverlap);
	ProjectileComponent->Activate();
}

void ACAddon_Projectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (AActor* actor : Ignores)
		CheckTrue(actor == OtherActor);

	Ignores.Add(OtherActor);

	IICharacter* iCharacter = Cast<IICharacter>(OtherActor);
	CheckNull(iCharacter);

	if (OnBeginOverlapEnemy.IsBound())	//CHaveAction_CreateProjectile ¼±¾ð
		OnBeginOverlapEnemy.Broadcast(Cast<ACharacter>(OtherActor), DamageType);
}

