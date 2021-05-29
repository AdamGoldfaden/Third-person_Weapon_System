#include "ProjectilePooler.h"
#include "Projectile_Base.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectilePooler::AProjectilePooler()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectilePooler::BeginPlay()
{
	Super::BeginPlay();

	for (uint8 i = 0; i < NumberOfProjectiles; i++)
	{
		AProjectile_Base* NewProjectile = GetWorld()->SpawnActor<AProjectile_Base>(ProjectileClass, GetActorLocation(), GetActorRotation());
		NewProjectile->SetProjectilePooler(this);
		NewProjectile->GetProjectileMovement()->Deactivate();

		ProjectilePool.Add(NewProjectile);
	}
}

AProjectile_Base* AProjectilePooler::SpawnNewProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	AProjectile_Base* NextProjectile = ProjectilePool[CurrentProjectileIndex];
	NextProjectile->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
	NextProjectile->GetProjectileMovement()->SetUpdatedComponent(NextProjectile->GetRootComponent());
	NextProjectile->GetProjectileMovement()->Velocity = NextProjectile->GetActorRotation().Vector() * NextProjectile->GetProjectileMovement()->InitialSpeed;
	NextProjectile->GetProjectileMovement()->Activate();

	CurrentProjectileIndex++;
	if (CurrentProjectileIndex >= ProjectilePool.Num())
	{
		CurrentProjectileIndex = 0;
	}

	return NextProjectile;
}

void AProjectilePooler::ReturnProjectile(AProjectile_Base* Projectile)
{
	Projectile->GetProjectileMovement()->Deactivate();
	Projectile->SetActorLocationAndRotation(GetActorLocation(), GetActorRotation());
}
