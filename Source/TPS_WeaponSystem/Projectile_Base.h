#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.generated.h"

class UProjectileMovementComponent;
class AProjectilePooler;

UCLASS()
class TPS_WEAPONSYSTEM_API AProjectile_Base : public AActor
{
	GENERATED_BODY()

public:
	AProjectile_Base();
	virtual void Tick(float DeltaTime) override;
	void AdjustVelocity();
	void SetProjectilePooler(AProjectilePooler* Pooler);

	UProjectileMovementComponent* GetProjectileMovement() { return ProjectileMovement; }

protected:
	virtual void BeginPlay() override;
	virtual void Explode();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
		const FHitResult& Hit) {}

	FVector InitialVelocity;
	AProjectilePooler* ProjectilePooler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleTrail;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|Explosion", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ExplosionRadius = 100.f;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|Explosion", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage = 20.f;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|Explosion", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ExplosionForce= 100000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_Base|Explosion", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ExplosionEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile_Base|Explosion", meta = (AllowPrivateAccess = "true"))
	float ExplosionEffectScale;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|ProjectileParams", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bShouldFollowPlayerVelocity = false;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|Controller Vibration", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float VibrationIntensity = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile_Base|Controller Vibration", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float VibrationDuration = 1.0f;
};
