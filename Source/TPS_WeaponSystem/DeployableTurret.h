#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeployableTurret.generated.h"

class AEnemyPawn;

UCLASS()
class TPS_WEAPONSYSTEM_API ADeployableTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ADeployableTurret();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void FindNextEnemyTarget();
	void FireBullet();

	AEnemyPawn* EnemyTarget;
	AActor* CurrentTarget;
	TArray<AEnemyPawn*> Enemies;
	FCollisionQueryParams Params;
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* FiringPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, Category = "DeployableTurret|Turret Params", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "DeployableTurret|Turret Params", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxDistance = 100000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "DeployableTurret|Weapons And Damage", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Damage = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "DeployableTurret|Weapons And Damage", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TimeBetweenShots = 0.05f;
	
};
