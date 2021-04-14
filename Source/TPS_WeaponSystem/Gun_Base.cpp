#include "Gun_Base.h"
#include "PlayerCharacter.h"

AGun_Base::AGun_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

bool AGun_Base::GunTrace(FHitResult& OutHit)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}

	FVector BulletStartLocation;
	FRotator BulletRotation;

	OwnerController->GetPlayerViewPoint(BulletStartLocation, BulletRotation);

	float AdjustedRadius = FMath::FRandRange(0.f, AccuracyRadius);

	APlayerCharacter* OwningPlayer = Cast<APlayerCharacter>(OwnerController->GetPawn());
	if (OwningPlayer == nullptr)
	{
		return false;
	}

	if (OwningPlayer->bIsCrouched)
	{
		AdjustedRadius *= CrouchMultiplier;
	}
	if (OwningPlayer->GetIsAiming())
	{
		AdjustedRadius *= AimingMultiplier;
	}
	if (OwningPlayer->GetVelocity().SizeSquared() > 0.f)
	{
		AdjustedRadius *= MovingMultiplier;
	}

	float AdjustedPitch = FMath::FRandRange(-AdjustedRadius, AdjustedRadius);
	float AdjustedYaw = FMath::Sqrt(FMath::Pow(AdjustedRadius, 2) - FMath::Pow(AdjustedPitch, 2));
	if (FMath::RandBool())
	{
		AdjustedYaw = -AdjustedYaw;
	}

	BulletRotation.Add(AdjustedPitch, AdjustedYaw, 0);
	FVector BulletEndLocation = BulletStartLocation + MaxRange * BulletRotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OutHit, BulletStartLocation, BulletEndLocation, ECC_GameTraceChannel1, Params);
}

FVector AGun_Base::GetDirectionFromStartToHit(FVector StartLocation, FHitResult HitResult) const
{
	FVector TraceDirection = (HitResult.Location - StartLocation).GetSafeNormal();
	return TraceDirection;
}

AController* AGun_Base::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) {
		return nullptr;
	}

	return OwnerPawn->GetController();
}