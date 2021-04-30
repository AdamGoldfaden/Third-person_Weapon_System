#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class APlayerCharacter;
class UTextBlock;
class UImage;

UCLASS()
class TPS_WEAPONSYSTEM_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* CurrentAmmoText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* MaxAmmoText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* GunTypeText;

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* GunTypeImage;

	UPROPERTY(meta = (BindWidgetOptional))
	UUserWidget* Reticle;

	UPROPERTY()
	APlayerCharacter* OwnerCharacter;
};
