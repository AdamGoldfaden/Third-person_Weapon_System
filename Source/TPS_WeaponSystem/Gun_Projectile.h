#pragma once

#include "CoreMinimal.h"
#include "Gun_Base.h"
#include "Gun_Projectile.generated.h"

class AProjectile_Base;

UCLASS()
class TPS_WEAPONSYSTEM_API AGun_Projectile : public AGun_Base
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile_Base> ProjectileClass;

public:
	AGun_Projectile();
	virtual void StartShooting() override;
	
};
