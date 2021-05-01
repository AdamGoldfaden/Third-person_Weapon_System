#include "Projectile_Base.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyPawn.h"
#include "Gun_Base.h"

AProjectile_Base::AProjectile_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile_Base::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);
}

void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	InitialVelocity = GetTransform().InverseTransformVector(ProjectileMovement->Velocity);
}

void AProjectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShouldFollowPlayerVelocity)
	{
		AdjustVelocity();
	}
}
	
void AProjectile_Base::AdjustVelocity()
{
	AActor* ActorThatShotProjectile = GetOwner()->GetOwner();
	if (!ActorThatShotProjectile) { return; }

	FVector NewProjectileLocalVelocity = InitialVelocity + GetTransform().InverseTransformVector(ActorThatShotProjectile->GetVelocity());
	ProjectileMovement->Velocity = GetTransform().TransformVector(NewProjectileLocalVelocity);
}

void AProjectile_Base::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), GetActorRotation(),
		FVector(ExplosionEffectScale, ExplosionEffectScale, ExplosionEffectScale));

	TArray<AActor*> HitActors;

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Init(this, 1);

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	UKismetSystemLibrary::SphereOverlapActors
	(
		GetWorld(),
		GetActorLocation(),
		ExplosionRadius,
		TraceObjectTypes,
		NULL, 
		IgnoreActors,
		HitActors
	);

	for (AActor* Actor : HitActors) 
	{
		FDamageEvent DamageEvent;
		Actor->TakeDamage(ExplosionDamage, DamageEvent, nullptr, this);

		UMeshComponent* MeshComponent = Actor->FindComponentByClass<UMeshComponent>();
		if (MeshComponent && Actor->IsRootComponentMovable() && MeshComponent->IsSimulatingPhysics())
		{
			MeshComponent->AddRadialImpulse(GetActorLocation(), ExplosionRadius, ExplosionForce, ERadialImpulseFalloff::RIF_Constant);
		}

		if (Cast<AEnemyPawn>(Actor))
		{
			if (AGun_Base* OwnerGun = Cast<AGun_Base>(GetOwner()))
			{
				OwnerGun->ShowHitMarker();
			}
		}
	}

	//DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 32, FColor::Red, false, 1.f);
}