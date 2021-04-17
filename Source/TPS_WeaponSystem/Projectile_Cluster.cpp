#include "Projectile_Cluster.h"
#include "GameFramework/ProjectileMovementComponent.h"

void AProjectile_Cluster::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	Destroy();
}

void AProjectile_Cluster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Simulate gravity in the local plane
	FVector CurrentVelocity = GetProjectileMovement()->Velocity;
	FVector TargetVelocity = CurrentVelocity + PlaneNormal * GRAVITY * GravityModifier;
	GetProjectileMovement()->Velocity = FMath::VInterpTo(CurrentVelocity, TargetVelocity, DeltaTime, 1000.f);
}
