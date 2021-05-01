#include "Gun_Base.h"
#include "PlayerCharacter.h"
#include "TPSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ReticleUserWidget.h"


AGun_Base::AGun_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun_Base::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
}

void AGun_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FiringMultiplier = FMath::FInterpTo(FiringMultiplier, 1.0f, DeltaTime, FiringMultiplierDecreaseRate);
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

	float AdjustedRadius = FMath::FRandRange(0.0f, AccuracyRadius);

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
	if (OwningPlayer->GetVelocity().SizeSquared() > 0.0f)
	{
		AdjustedRadius *= MovingMultiplier;
	}

	float AdjustedPitch = FMath::FRandRange(-AdjustedRadius, AdjustedRadius);
	float AdjustedYaw = FMath::Sqrt(FMath::Pow(AdjustedRadius, 2.0f) - FMath::Pow(AdjustedPitch, 2.0f));
	if (FMath::RandBool())
	{
		AdjustedYaw = -AdjustedYaw;
	}

	BulletRotation.Add(AdjustedPitch, AdjustedYaw, 0.0f);
	FVector BulletEndLocation = BulletStartLocation + MaxRange * BulletRotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OutHit, BulletStartLocation, BulletEndLocation, ECC_GameTraceChannel1, Params);
}

FVector AGun_Base::GetDirectionFromStartToHit(const FVector& StartLocation, FHitResult HitResult) const
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

void AGun_Base::StartShooting() 
{ 
	bIsShooting = true; 
}

void AGun_Base::StopShooting()
{ 
	bIsShooting = false; 
}

void AGun_Base::Reload() 
{
	if (bIsReloading || CurrentAmmo == MaxAmmo)
	{
		return;
	}

	bIsReloading = true;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AGun_Base::StopReloading, ReloadTime, false);
}

void AGun_Base::StopReloading()
{
	CurrentAmmo = MaxAmmo;
	bIsReloading = false;
}

void AGun_Base::ApplyDamage(const FHitResult& Hit)
{
	AActor* HitActor = Hit.GetActor();
	if (HitActor == nullptr)
	{
		return;
	}

	FPointDamageEvent DamageEvent(Damage, Hit, Hit.Normal, nullptr);
	Hit.Actor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
}

float AGun_Base::GetAccuracyMultiplier() const
{
	APlayerCharacter* OwnerPlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (!OwnerPlayerCharacter)
	{
		return 1.0f;
	}

	float AccuracyMultiplier = AccuracyRadius;
	if (OwnerPlayerCharacter->bIsCrouched)
	{
		AccuracyMultiplier *= CrouchMultiplier;
	}
	if (OwnerPlayerCharacter->GetIsAiming())
	{
		AccuracyMultiplier *= AimingMultiplier;
	}
	if (OwnerPlayerCharacter->GetVelocity().SizeSquared() > 0.0f)
	{
		AccuracyMultiplier *= MovingMultiplier;
	}

	AccuracyMultiplier *= FiringMultiplier;

	return AccuracyMultiplier;
}

void AGun_Base::ConsumeAmmo(uint8 AmmoToConsume)
{
	CurrentAmmo -= AmmoToConsume;
	if (CurrentAmmo <= 0)
	{
		Reload();
	}
}

void AGun_Base::IncreaseFiringMultiplier(float AmountToIncrease)
{
	FiringMultiplier += AmountToIncrease;
}

void AGun_Base::ResetFiringMultiplier()
{
	FiringMultiplier = 1.0f;
}

void AGun_Base::ShowHitMarker()
{
	ATPSPlayerController* OwnerPlayerController = Cast<ATPSPlayerController>(GetOwnerController());
	if (!OwnerPlayerController)
	{
		return;
	}

	UReticleUserWidget* ReticleWidget = Cast<UReticleUserWidget>(OwnerPlayerController->GetReticle());
	if (!ReticleWidget)
	{
		return;
	}

	ReticleWidget->ShowHitMarker();
}