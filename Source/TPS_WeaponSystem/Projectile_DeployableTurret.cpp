#include "Projectile_DeployableTurret.h"
#include "DeployableTurret.h"
#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"

void AProjectile_DeployableTurret::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	
	if (Cast<AEnemyPawn>(OtherActor))
	{
		Destroy();
		return;
	}

	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMesh->SetVisibility(false);

	if (AActor* CurrentTurret = UGameplayStatics::GetActorOfClass(this, ADeployableTurret::StaticClass()))
	{
		CurrentTurret->Destroy();
	}

	const FVector& TurretSpawnLocation = Hit.Location;
	const FRotator& TurretSpawnRotation = FRotationMatrix::MakeFromZ(Hit.Normal).Rotator();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ADeployableTurret* NewTurret = GetWorld()->SpawnActor<ADeployableTurret>(TurretClass, TurretSpawnLocation, TurretSpawnRotation, SpawnParameters);
	NewTurret->SetOwner(this);
	NewTurret->AttachToActor(Hit.GetActor(), FAttachmentTransformRules::KeepWorldTransform);

	Destroy();
} 