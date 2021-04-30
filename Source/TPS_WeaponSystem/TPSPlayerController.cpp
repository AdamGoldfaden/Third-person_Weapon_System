#include "TPSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ReticleUserWidget.h"
#include "Gun_Base.h"

void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}

void ATPSPlayerController::ChangeReticle(TSubclassOf<UUserWidget> ReticleWidgetClass)
{
	if (Reticle)
	{
		Reticle->RemoveFromViewport();
	}

	Reticle = CreateWidget(this, ReticleWidgetClass);
	if (!Reticle)
	{
		return;
	}

	Reticle->AddToViewport();
}