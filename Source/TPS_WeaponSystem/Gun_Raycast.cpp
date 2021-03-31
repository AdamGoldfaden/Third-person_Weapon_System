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
		FVector Direction = GetDirectionFromStartToHit(StartLocation, OutHit);
		FVector EndLocation = StartLocation + (MaxRange * Direction) + GetOwner()->GetVelocity();
		DrawDebugPoint(GetWorld(), OutHit.Location, 10.f, FColor::Red, false, 0.25f);
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 0.1f);
	}
}