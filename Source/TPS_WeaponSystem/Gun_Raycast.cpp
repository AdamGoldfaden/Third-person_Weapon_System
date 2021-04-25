#include "Gun_Raycast.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"

void AGun_Raycast::StartShooting()
{
	Super::StartShooting();

	FireBullet();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AGun_Raycast::FireBullet, TimeBetweenShots, true);
}

void AGun_Raycast::StopShooting()
{
	Super::StopShooting();

	GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
}

void AGun_Raycast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShooting && !bIsReloading)
	{
		//Add Recoil
		FRotator CurrentControllerRotation = GetOwnerController()->GetControlRotation();
		FRotator TargetControllerRotation = CurrentControllerRotation.Add(VerticalRecoilAmount, HorizontalRecoilAmount, 0.f);
		FRotator NewControllerRotation = FMath::RInterpTo(CurrentControllerRotation, TargetControllerRotation, DeltaTime, RecoilSpeed);
		GetOwnerController()->SetControlRotation(NewControllerRotation);
	}
}

void AGun_Raycast::FireBullet()
{
	if (bIsReloading)
	{
		return;
	}
	
	FHitResult OutHit;
	if (!GunTrace(OutHit))
	{
		return;
	}

	FVector StartLocation = GetGunMesh()->GetSocketLocation(TEXT("MuzzleSocket"));
	FVector Direction = GetDirectionFromStartToHit(StartLocation, OutHit);
	FVector EndLocation = StartLocation + (MaxRange * Direction) + GetOwner()->GetVelocity();

	DrawDebugPoint(GetWorld(), OutHit.Location, 5.f, FColor::Red, false, 0.25f);
	DrawDebugLine(GetWorld(), StartLocation, OutHit.Location, FColor::Red, false, 0.2f);
	
	ApplyDamage(OutHit);

	UMeshComponent* MeshComponent = OutHit.GetActor()->FindComponentByClass<UMeshComponent>();
	if (MeshComponent && OutHit.GetActor()->IsRootComponentMovable() && MeshComponent->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Warning, TEXT("Raycast gun hit: %s"), *OutHit.GetActor()->GetName());
		MeshComponent->AddImpulseAtLocation(-OutHit.ImpactNormal * ImpulseForce, OutHit.Location);
	}

	CurrentAmmo--;
	if (CurrentAmmo <= 0)
	{
		Reload();
	}
}