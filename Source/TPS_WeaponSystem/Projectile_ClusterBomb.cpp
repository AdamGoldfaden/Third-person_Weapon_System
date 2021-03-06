#include "Projectile_ClusterBomb.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile_Cluster.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectilePooler.h"


void AProjectile_ClusterBomb::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, AProjectilePooler::StaticClass(), TEXT("Cluster"), OutActors);
	if (OutActors.Num() >= 0)
	{
		ProjectilePooler = Cast<AProjectilePooler>(OutActors[0]);
	}
}

void AProjectile_ClusterBomb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMesh->SetVisibility(false);

	Explode();

	FVector ProjectileSpawnLocation = Hit.Location;
	ProjectileSpawnLocation += (ProjectileSpawnHeight * Hit.Normal);

	FRotator InitialSpawnRotation = Hit.Normal.Rotation();
	float AngleToRotate = 360.f / NumberOfProjectiles;

	for (uint8 i = 0; i < NumberOfProjectiles; i++)
	{
		FRotator ProjectileSpawnRotation = InitialSpawnRotation;
		ProjectileSpawnRotation.Add(ProjectileSpawnPitch, i * AngleToRotate, 0.f);

		/*ProjectileSpawnRotation.Add(ProjectileSpawnPitch, 0.f, 0.f);
		ProjectileSpawnRotation = ProjectileSpawnRotation.Vector().RotateAngleAxis(i * AngleToRotate, Hit.Normal).Rotation();

		AProjectile_Cluster* Projectile = GetWorld()->SpawnActor<AProjectile_Cluster>(ClusterProjectileClass, ProjectileSpawnLocation, 
			ProjectileSpawnRotation);*/

		AProjectile_Cluster* Projectile = Cast<AProjectile_Cluster>(ProjectilePooler->SpawnNewProjectile(ProjectileSpawnLocation, ProjectileSpawnRotation));
		Projectile->PlaneNormal = Hit.Normal;
		Projectile->SetOwner(GetOwner());
	}

	Destroy();
}