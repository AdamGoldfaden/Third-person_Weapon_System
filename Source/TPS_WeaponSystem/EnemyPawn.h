#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyPawn.generated.h"

class UWidgetComponent;
class APlayerCharacter;

UCLASS()
class TPS_WEAPONSYSTEM_API AEnemyPawn : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBar;

	float CurrentHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyPawn|Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;
	bool bIsDead = false;

	APlayerCharacter* Player;

	void Die();

protected:
	virtual void BeginPlay() override;

public:
	AEnemyPawn();
	virtual void Tick(float DeltaTime) override;

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	FORCEINLINE float GetHealth() const { return CurrentHealth; }
	FORCEINLINE float GetHealthPercentage() const {return CurrentHealth / MaxHealth;}
	FORCEINLINE float IsDead() const { return bIsDead; }
};
