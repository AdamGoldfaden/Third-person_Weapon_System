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

public:
	AEnemyPawn();
	virtual void Tick(float DeltaTime) override;

	void Revive();

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	FORCEINLINE float GetHealth() const { return CurrentHealth; }
	FORCEINLINE float GetHealthPercentage() const { return CurrentHealth / MaxHealth; }
	FORCEINLINE float IsDead() const { return bIsDead; }
	FORCEINLINE FTransform GetStartingMeshTransform() const { return StartingMeshTransform; }

protected:
	virtual void BeginPlay() override;

private:
	void Die();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthBar;

	float CurrentHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyPawn|Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;
	bool bIsDead = false;

	APlayerCharacter* Player;
	FTransform StartingMeshTransform;
};
