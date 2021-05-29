#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectilePooler.generated.h"

class AProjectile_Base;

UCLASS()
class TPS_WEAPONSYSTEM_API AProjectilePooler : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectilePooler();

	AProjectile_Base* SpawnNewProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation);
	void ReturnProjectile(AProjectile_Base* Projectile);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectilePooler|Projectiles", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile_Base> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectilePooler|Projectiles", meta = (AllowPrivateAccess = "true"))
	uint8 NumberOfProjectiles = 0;

	TArray<AProjectile_Base*> ProjectilePool;
	uint8 CurrentProjectileIndex = 0;
	
};
