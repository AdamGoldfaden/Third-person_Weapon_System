#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_ClusterBomb.generated.h"

class AProjectile_Cluster;

UCLASS()
class TPS_WEAPONSYSTEM_API AProjectile_ClusterBomb : public AProjectile_Base
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_ClubsterBomb|Cluster", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile_Cluster> ClusterProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_ClubsterBomb|Cluster", meta = (AllowPrivateAccess = "true"))
	float ProjectileSpawnHeight = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_ClubsterBomb|Cluster", meta = (AllowPrivateAccess = "true"))
	float ProjectileSpawnPitch = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_ClubsterBomb|Cluster", meta = (AllowPrivateAccess = "true"))
	uint8 NumberOfProjectiles = 8;

protected:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit) override;
};
