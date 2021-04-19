#include "Gun_Projectile.h"
#include "Projectile_Base.h"
#include "GameFramework/ProjectileMovementComponent.h"


AGun_Projectile::AGun_Projectile()
{
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GetGunMesh());
}

void AGun_Projectile::StartShooting()
{
	if (bIsReloading)
	{
		return;
	}

	FHitResult OutHit;
	if (GunTrace(OutHit))
	{
		const FVector& ProjectileSpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		const FRotator& ProjectileSpawnRotation = GetDirectionFromStartToHit(ProjectileSpawnLocation, OutHit).Rotation();

		AProjectile_Base* Projectile = GetWorld()->SpawnActor<AProjectile_Base>
		(
			ProjectileClass, 
			ProjectileSpawnLocation, 
			ProjectileSpawnRotation
		);

		Projectile->SetOwner(this);
		Projectile->AdjustVelocity();

		CurrentAmmo--;
		if (CurrentAmmo <= 0)
		{
			Reload();
		}
	}
}