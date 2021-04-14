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
	FVector InitialVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit) {}

public:	
	AProjectile_Base();
	virtual void Tick(float DeltaTime) override;
	void AdjustVelocity();
};
