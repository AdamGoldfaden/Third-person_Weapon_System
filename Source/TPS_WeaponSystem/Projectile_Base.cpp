#include "Projectile_Base.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

AProjectile_Base::AProjectile_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile_Base::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
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