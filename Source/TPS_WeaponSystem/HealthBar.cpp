#include "HealthBar.h"
#include "Components/ProgressBar.h"
#include "EnemyPawn.h"

void UHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (HealthBar)
	{
		if (OwnerEnemyPawn)
		{
			float NewHealth = FMath::FInterpTo(HealthBar->Percent, OwnerEnemyPawn->GetHealthPercentage(), InDeltaTime, HealthChangeSpeed);
			HealthBar->SetPercent(NewHealth);
		}
	}
}