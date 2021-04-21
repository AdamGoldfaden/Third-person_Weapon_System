#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class AEnemyPawn;
class UProgressBar;

UCLASS()
class TPS_WEAPONSYSTEM_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidgetOptional))
	UProgressBar* HealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBar|Speed", meta = (AllowPrivateAccess = "true"))
	float HealthChangeSpeed = 10.f;

	AEnemyPawn* OwnerEnemyPawn;
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	FORCEINLINE void SetOwnerEnemyPawn(AEnemyPawn* EnemyPawn) { OwnerEnemyPawn = EnemyPawn; }
};
