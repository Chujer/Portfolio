#include "Characters/AnimInstances/CAnimInstance_Base_Player.h"

#include "GameFramework/Character.h"
#include "Global.h"

void UCAnimInstance_Base_Player::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);

	if (!!Weapon)
		Weapon->OnWeaponTypeChange.AddDynamic(this, &UCAnimInstance_Base_Player::OnWeaponTypeChanged);
}

void UCAnimInstance_Base_Player::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();


}

void UCAnimInstance_Base_Player::OnWeaponTypeChanged(EWeaponType InPreType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}
