#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReticleUserWidget.generated.h"

class APlayerCharacter;
class UImage;

UCLASS()
class TPS_WEAPONSYSTEM_API UReticleUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowHitMarker();
	void HideHitMarker();

protected:
	virtual void NativeConstruct() override;
	FORCEINLINE APlayerCharacter* GetOwnerCharacter() const { return OwnerCharacter; }
private:
	FTimerHandle HitMarkerTimerHandle;

	UPROPERTY()
	APlayerCharacter* OwnerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ReticleUserWidget|HitMarker", meta = (AllowPrivateAccess = "true"))
	float HitMarkerVisibilityTime = 0.5f;
	
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* HitMarker;
};
