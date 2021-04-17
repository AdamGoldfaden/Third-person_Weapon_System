#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Cluster.generated.h"

UCLASS()
class TPS_WEAPONSYSTEM_API AProjectile_Cluster : public AProjectile_Base
{
	GENERATED_BODY()

private:
	const float GRAVITY = -9.81;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_Cluster|Gravity", meta = (AllowPrivateAccess = "true"))
	float GravityModifier = 1.f;

protected:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit) override;

public:
	FVector PlaneNormal;

	virtual void Tick(float DeltaTime) override;
	
};
