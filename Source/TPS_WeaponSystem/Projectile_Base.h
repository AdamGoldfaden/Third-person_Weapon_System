#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TPS_WEAPONSYSTEM_API AProjectile_Base : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|ProjectileParams", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bShouldFollowPlayerVelocity = false;

protected:
	FVector InitialVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|Explosion", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ExplosionRadius = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|Explosion", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage = 20.f;

	virtual void BeginPlay() override;
	virtual void Explode();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit) {}

public:	
	AProjectile_Base();
	virtual void Tick(float DeltaTime) override;
	void AdjustVelocity();

	UProjectileMovementComponent* GetProjectileMovement() { return ProjectileMovement; }
};
