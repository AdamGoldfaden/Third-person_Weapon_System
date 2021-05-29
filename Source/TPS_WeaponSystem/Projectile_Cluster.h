#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Projectile_Cluster.generated.h"

UCLASS()
class TPS_WEAPONSYSTEM_API AProjectile_Cluster : public AProjectile_Base
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	FVector PlaneNormal;

protected:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit) override;

private:
	static const float GRAVITY; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_Cluster|Gravity", meta = (AllowPrivateAccess = "true"))
	float GravityModifier = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_Cluster|Gravity", meta = (AllowPrivateAccess = "true"))
	bool bShouldUseArtificialGravity = false;
};
