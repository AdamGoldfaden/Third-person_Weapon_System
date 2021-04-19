#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun_Base.generated.h"

UENUM(BlueprintType)
enum EGunType
{
	Auto UMETA(DisplayName, "AutoRifle"),
	Cluster UMETA(DisplayName, "ClusterBomb")
};

UCLASS()
class TPS_WEAPONSYSTEM_API AGun_Base : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Gun Info", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EGunType> GunType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Gun Info", meta = (AllowPrivateAccess = "true"))
	UTexture2D* GunTypeImage;

	FTimerHandle ReloadTimerHandle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Ammo and Reloading", meta = (AllowPrivateAccess = "true"))
	float ReloadTime = 1.f;


protected:
	bool bIsShooting = false;
	bool bIsReloading = false;
	uint8 CurrentAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Gun Info", meta = (AllowPrivateAccess = "true"))
	float MaxRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy", meta = (AllowPrivateAccess = "true"))
	float AccuracyRadius = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Ammo and Reloading", meta = (AllowPrivateAccess = "true"))
	uint8 MaxAmmo = 10.f;

	virtual void BeginPlay() override;
	virtual bool GunTrace(FHitResult& OutHit);
	virtual FVector GetDirectionFromStartToHit(FVector StartLocation, FHitResult HitResult) const;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy", meta = (AllowPrivateAccess = "true"))
	float CrouchMultiplier = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy", meta = (AllowPrivateAccess = "true"))
	float AimingMultiplier = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy", meta = (AllowPrivateAccess = "true"))
	float MovingMultiplier = 2.f;

	AGun_Base();
	virtual void StartShooting();
	virtual void StopShooting();
	virtual void Reload();
	virtual void StopReloading();

	AController* GetOwnerController() const;
	FORCEINLINE EGunType GetGunType() const { return GunType; };
	FORCEINLINE UTexture2D* GetGunTypeImage() const { return GunTypeImage; };
	FORCEINLINE USkeletalMeshComponent* GetGunMesh() const { return Mesh; };
	FORCEINLINE float GetAccuracy() const { return AccuracyRadius; };
	FORCEINLINE uint8 GetCurrentAmmo() const { return CurrentAmmo; };
	FORCEINLINE uint8 GetMaxAmmo() const { return MaxAmmo; };
}; 
