#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReticleUserWidget.generated.h"

class UImage;
class APlayerCharacter;

UCLASS()
class TPS_WEAPONSYSTEM_API UReticleUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CrossHair_Bottom;
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CrossHair_Top;
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CrossHair_Right;
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CrossHair_Left;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float AccuracyTranslation = 20.f;

	void SetCrossHairPosition();

	UPROPERTY()
	APlayerCharacter* OwnerCharacter;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:
	float AccuracyMultiplier = 1.f;

};
