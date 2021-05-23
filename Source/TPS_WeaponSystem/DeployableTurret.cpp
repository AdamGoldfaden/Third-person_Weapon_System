#include "DeployableTurret.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "EnemyPawn.h"

ADeployableTurret::ADeployableTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->SetupAttachment(Root);

	FiringPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Firing Point"));
	FiringPoint->SetupAttachment(TurretMesh);
}

void ADeployableTurret::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> EnemyActors;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemyPawn::StaticClass(), EnemyActors);

	for (AActor* EnemyActor : EnemyActors)
	{
		Enemies.Add(Cast<AEnemyPawn>(EnemyActor));
	}

	Params.AddIgnoredActor(this);

	FindNextEnemyTarget();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ADeployableTurret::FireBullet, TimeBetweenShots, true);
}

void ADeployableTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult OutHit;
	const FVector& StartLocation = FiringPoint->GetComponentLocation();
	const FVector& EndLocation = StartLocation + (FiringPoint->GetComponentRotation().Vector() * MaxDistance);
	const bool& DidHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_GameTraceChannel3, Params);

	if (!DidHit)
	{
		return;
	}

	CurrentTarget = OutHit.GetActor();
	DrawDebugLine(GetWorld(), StartLocation, OutHit.Location, FColor::Red, false);

	if (!EnemyTarget)
	{
		return;
	}

	const FRotator& TargetTurretRotation = (EnemyTarget->GetActorLocation() - GetActorLocation()).Rotation();
	const FRotator& NewRotation = FMath::RInterpConstantTo(TurretMesh->GetComponentRotation(), TargetTurretRotation, DeltaTime, RotationSpeed);

	TurretMesh->SetWorldRotation(NewRotation);
}

void ADeployableTurret::FindNextEnemyTarget()
{
	EnemyTarget = nullptr;
	float CurrentMinDistance = TNumericLimits<float>::Max();
	for (AEnemyPawn* Enemy : Enemies)
	{
		if (Enemy->IsDead())
		{
			continue;
		}

		float Distance = FVector::DistSquared(GetActorLocation(), Enemy->GetActorLocation());
		if (Distance < CurrentMinDistance)
		{
			CurrentMinDistance = Distance;
			EnemyTarget = Enemy;
		}
	}
}

void ADeployableTurret::FireBullet()
{
	if (AEnemyPawn* Enemy = Cast<AEnemyPawn>(CurrentTarget))
	{
		Enemy->TakeDamage(Damage, FDamageEvent::FDamageEvent(), GetInstigatorController(), this);
	}
	else
	{
		FindNextEnemyTarget();
	}
}
