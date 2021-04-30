#include "ReticleUserWidget.h"
#include "PlayerCharacter.h"
#include "Components/Image.h"


void UReticleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
}

void UReticleUserWidget::ShowHitMarker()
{
	HitMarker->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(HitMarkerTimerHandle, this, &UReticleUserWidget::HideHitMarker, HitMarkerVisibilityTime);
}

void UReticleUserWidget::HideHitMarker()
{
	if (HitMarker)
	{
		HitMarker->SetVisibility(ESlateVisibility::Hidden);
	}
}