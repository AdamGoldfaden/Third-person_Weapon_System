#include "PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerCharacter.h"
#include "Gun_Base.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());

}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!OwnerCharacter)
	{
		return;
	}

	AGun_Base* OwnerCharacterGun = OwnerCharacter->GetGun();

	if (CurrentAmmoText != nullptr)
	{
		CurrentAmmoText->SetText(FText::AsNumber(OwnerCharacterGun->GetCurrentAmmo()));
	}
	if (MaxAmmoText != nullptr)
	{
		MaxAmmoText->SetText(FText::AsNumber(OwnerCharacterGun->GetMaxAmmo()));
	}
	if (GunTypeImage != nullptr)
	{
		GunTypeImage->SetBrushFromTexture(OwnerCharacterGun->GetGunTypeImage());
	}
	/*if (GunTypeText != nullptr)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGunType"), true);
		uint8 EnumValue = static_cast<uint8>(OwnerCharacterGun->GetGunType());
		GunTypeText->SetText(EnumPtr->GetDisplayNameText(EnumValue));
	}*/
}