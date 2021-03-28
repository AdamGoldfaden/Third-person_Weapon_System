#include "Gun_Projectile.h"
#include "Projectile_Base.h"


AGun_Projectile::AGun_Projectile()
{
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GetGunMesh());
}

void AGun_Projectile::StartShooting()
{
	FHitResult OutHit;
	if (GunTrace(OutHit))
	{
		FVector ProjectileSpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator ProjectileSpawnRotation = GetTraceDirection(OutHit).Rotation();
		AProjectile_Base* Projectile = GetWorld()->SpawnActor<AProjectile_Base>(ProjectileClass, ProjectileSpawnLocation, 
			ProjectileSpawnRotation);
		Projectile->SetOwner(this);
	}
}