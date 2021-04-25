#include "Gun_Raycast.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

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

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetGunMesh(), TEXT("MuzzleSocket"), FVector(ForceInit), FRotator::ZeroRotator, 
		FVector(MuzzleFlashScale, MuzzleFlashScale, MuzzleFlashScale));

	FVector StartLocation = GetGunMesh()->GetSocketLocation(TEXT("MuzzleSocket"));
	FVector Direction = GetDirectionFromStartToHit(StartLocation, OutHit);
	FVector EndLocation = StartLocation + (MaxRange * Direction) + GetOwner()->GetVelocity();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHit.Location, OutHit.Normal.Rotation(), 
		FVector(ImpactEffectScale, ImpactEffectScale, ImpactEffectScale));

	/*DrawDebugPoint(GetWorld(), OutHit.Location, 5.f, FColor::Red, false, 0.25f);
	DrawDebugLine(GetWorld(), StartLocation, OutHit.Location, FColor::Red, false, 0.2f);*/
	
	ApplyDamage(OutHit);

	UMeshComponent* MeshComponent = OutHit.GetActor()->FindComponentByClass<UMeshComponent>();
	if (MeshComponent && OutHit.GetActor()->IsRootComponentMovable() && MeshComponent->IsSimulatingPhysics())
	{
		MeshComponent->AddImpulseAtLocation(-OutHit.ImpactNormal * ImpulseForce, OutHit.Location);
	}

	CurrentAmmo--;
	if (CurrentAmmo <= 0)
	{
		Reload();
	}
}