#include "Gun_Raycast.h"
#include "DrawDebugHelpers.h"

void AGun_Raycast::StartShooting()
{
	UE_LOG(LogTemp, Warning, TEXT("Got here"));
	FHitResult OutHit;
	if (GunTrace(OutHit))
	{
		FVector StartLocation = GetGunMesh()->GetSocketLocation(TEXT("MuzzleSocket"));
		FVector Direction = GetTraceDirection(StartLocation, OutHit);
		FVector EndLocation = StartLocation + MaxRange * Direction;
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 0.25f);
		DrawDebugPoint(GetWorld(), OutHit.Location, 10.f, FColor::Red, false, 0.25f);
	}
}