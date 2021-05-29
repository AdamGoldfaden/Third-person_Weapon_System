#include "Projectile_Cluster.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectilePooler.h"

const float AProjectile_Cluster::GRAVITY = - 9.81;

void AProjectile_Cluster::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	Explode();

	ProjectilePooler->ReturnProjectile(this);
}

void AProjectile_Cluster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldUseArtificialGravity)
	{
		//Simulate gravity in the local plane
		FVector CurrentVelocity = GetProjectileMovement()->Velocity;
		FVector TargetVelocity = CurrentVelocity + PlaneNormal * GRAVITY * GravityModifier;
		GetProjectileMovement()->Velocity = FMath::VInterpTo(CurrentVelocity, TargetVelocity, DeltaTime, 1000.f);
	}
}
