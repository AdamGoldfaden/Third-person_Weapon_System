#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_DeployableTurret.generated.h"

class ADeployableTurret;

UCLASS()
class TPS_WEAPONSYSTEM_API AProjectile_DeployableTurret : public AProjectile_Base
{
	GENERATED_BODY()
	
protected:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit) override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_DeployableTurret|Turret", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ADeployableTurret> TurretClass;

};
