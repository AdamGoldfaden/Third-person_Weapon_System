#include "Gun_Raycast.h"
#include "DrawDebugHelpers.h"

void AGun_Raycast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugPoint(GetWorld(), GetGunMesh()->GetSocketLocation(TEXT("MuzzleSocket")), 10.0f, FColor::Red);
}

void AGun_Raycast::StartShooting()
{
	UE_LOG(LogTemp, Warning, TEXT("Got here"));
	FHitResult OutHit;
	if (GunTrace(OutHit))
	{
		FVector StartLocation = GetGunMesh()->GetSocketLocation(TEXT("MuzzleSocket"));
		FVector Direction = GetTraceDirection(OutHit);
		FVector EndLocation = StartLocation + MaxRange * Direction;
		DrawDebugPoint(GetWorld(), OutHit.Location, 10.f, FColor::Red, false, 0.25f);
	}
}