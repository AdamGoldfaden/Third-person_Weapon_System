#pragma once

#include "CoreMinimal.h"
#include "ReticleUserWidget.h"
#include "AccuracyReticleUserWidger.generated.h"

class UImage;
class APlayerCharacter;

UCLASS()
class TPS_WEAPONSYSTEM_API UAccuracyReticleUserWidger : public UReticleUserWidget
{
	GENERATED_BODY()

public:
	float AccuracyMultiplier = 1.f;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void SetCrossHairPosition();

	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CrossHair_Bottom;
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CrossHair_Top;
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CrossHair_Right;
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* CrossHair_Left;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ReticleUserWidget|Accuracy", meta = (AllowPrivateAccess = "true"))
	float AccuracyTranslation = 20.0f;
};
