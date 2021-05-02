#include "ReticleUserWidget.h"
#include "PlayerCharacter.h"
#include "Components/Image.h"


void UReticleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	HideHitMarker();
}

void UReticleUserWidget::ShowHitMarker()
{
	if (HitMarker->GetVisibility() == ESlateVisibility::Visible)
	{
		return;
	}
	HitMarker->SetColorAndOpacity(FLinearColor::White);
	HitMarker->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(HitMarkerTimerHandle, this, &UReticleUserWidget::HideHitMarker, HitMarkerVisibilityTime);
}

void UReticleUserWidget::ShowCritHitMarker()
{
	if (HitMarker->GetVisibility() == ESlateVisibility::Visible)
	{
		return;
	}
	HitMarker->SetColorAndOpacity(FLinearColor::Red);
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