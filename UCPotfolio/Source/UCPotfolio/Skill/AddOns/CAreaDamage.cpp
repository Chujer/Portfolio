#include "Skill/AddOns/CAreaDamage.h"
#include "Weapon/CAttachment.h"
#include "Global.h"
#include "Components/CWeaponComponent.h"

ACAreaDamage::ACAreaDamage()
{
}

void ACAreaDamage::BeginPlay()
{
	Super::BeginPlay();
	CheckNull(GetOwner());
	Character = Cast<ACharacter>(GetOwner());
	Attachment = CHelpers::GetComponent<UCWeaponComponent>(Character)->GetAttachment();
	Ignores.Add(Character);
	Ignores.Add(Attachment);
}

void ACAreaDamage::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
