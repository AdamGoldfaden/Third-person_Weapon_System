#include "Projectile_Base.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"



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

void AProjectile_Base::Explode()
{

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

	for (AActor* Actor : HitActors) {

		UE_LOG(LogTemp, Warning, TEXT("OverlappedActor: %s"), *Actor->GetName());
		////float ScaledDamage = ExplosionDamage - (FVector::Distance(GetActorLocation(), Actor->GetActorLocation())/ExplosionRadius * ExplosionDamage);
		//UE_LOG(LogTemp, Warning, TEXT("Scaled Damage: %f"), ScaledDamage);

		FDamageEvent DamageEvent;

		Actor->TakeDamage(ExplosionDamage, DamageEvent, nullptr, this);
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 32, FColor::Red, false, 1.f);


}