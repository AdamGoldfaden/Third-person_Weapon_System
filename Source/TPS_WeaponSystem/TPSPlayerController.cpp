#include "TPSPlayerController.h"
#include "Blueprint/UserWidget.h"

void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}