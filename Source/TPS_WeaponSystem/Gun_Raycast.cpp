#include "Gun_Raycast.h"
#include "DrawDebugHelpers.h"

void AGun_Raycast::StartShooting()
{
	FireBullet();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &AGun_Raycast::FireBullet, TimeBetweenShots, true);
}

void AGun_Raycast::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
}

void AGun_Raycast::FireBullet()
{
	FHitResult OutHit;
	if (GunTrace(OutHit))
	{
		FVector StartLocation = GetGunMesh()->GetSocketLocation(TEXT("MuzzleSocket"));
		FVector Direction = GetDirectionFromStartToHit(StartLocation, OutHit);
		FVector EndLocation = StartLocation + (MaxRange * Direction) + GetOwner()->GetVelocity();
		DrawDebugPoint(GetWorld(), OutHit.Location, 5.f, FColor::Red, false, 0.25f);
		DrawDebugLine(GetWorld(), StartLocation, OutHit.Location, FColor::Red, false, 0.2f);
	}
}

