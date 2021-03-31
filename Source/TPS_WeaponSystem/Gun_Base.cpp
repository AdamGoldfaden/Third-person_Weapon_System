#include "Gun_Base.h"

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
	FVector BulletEndLocation = BulletStartLocation + MaxRange * BulletRotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OutHit, BulletStartLocation, BulletEndLocation, ECC_GameTraceChannel1, Params);
}

FVector AGun_Base::GetTraceDirection(FHitResult HitResult) const
{
	return (HitResult.Location - GetGunMesh()->GetSocketLocation("WeaponSocket")).GetSafeNormal();
}

AController* AGun_Base::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) {
		return nullptr;
	}

	return OwnerPawn->GetController();
}