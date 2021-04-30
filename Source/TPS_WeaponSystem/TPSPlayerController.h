#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSPlayerController.generated.h"

class UUserWidget;
class UReticleUserWidget;
class AGun_Base;

UCLASS()
class TPS_WEAPONSYSTEM_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ChangeReticle(TSubclassOf<UUserWidget> ReticleWidgetClass);

	FORCEINLINE UUserWidget* GetHUD() const { return HUD; }
	FORCEINLINE UUserWidget* GetReticle() const { return Reticle; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY()
	UUserWidget* Reticle;
};
