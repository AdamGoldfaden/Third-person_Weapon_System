#include "HealthBar.h"
#include "Components/ProgressBar.h"
#include "EnemyPawn.h"

void UHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!HealthBar)
	{
		return;
	}

	if (!OwnerEnemyPawn)
	{
		return;
	}

	float NewHealth = FMath::FInterpTo(HealthBar->Percent, OwnerEnemyPawn->GetHealthPercentage(), InDeltaTime, HealthChangeSpeed);
	HealthBar->SetPercent(NewHealth);
}