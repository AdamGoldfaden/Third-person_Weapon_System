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

class UUserWidget;

UCLASS()
class TPS_WEAPONSYSTEM_API AGun_Base : public AActor
{
	GENERATED_BODY()

public:	
	AGun_Base();
	void ConsumeAmmo(uint8 AmmoToConsume);
	virtual void Tick(float DeltaTime) override;
	virtual void StartShooting();
	virtual void StopShooting();
	virtual void Reload();
	virtual void StopReloading();
	virtual void ApplyDamage(const FHitResult& Hit);

	void IncreaseFiringMultiplier(float AmountToIncrease);
	void ResetFiringMultiplier();

	AController* GetOwnerController() const;
	float GetAccuracyMultiplier() const;
	FORCEINLINE EGunType GetGunType() const { return GunType; };
	FORCEINLINE UTexture2D* GetGunTypeImage() const { return GunTypeImage; };
	FORCEINLINE USkeletalMeshComponent* GetGunMesh() const { return Mesh; };
	FORCEINLINE float GetAccuracyRadius() const { return AccuracyRadius; };
	FORCEINLINE uint8 GetCurrentAmmo() const { return CurrentAmmo; };
	FORCEINLINE uint8 GetMaxAmmo() const { return MaxAmmo; };
	FORCEINLINE TSubclassOf<UUserWidget> GetReticleWidgetClass() const { return ReticleWidgetClass; }

	bool bIsShooting = false;
	bool bIsReloading = false;
	uint8 CurrentAmmo = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy", meta = (AllowPrivateAccess = "true"))
	float CrouchMultiplier = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy", meta = (AllowPrivateAccess = "true"))
	float AimingMultiplier = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy", meta = (AllowPrivateAccess = "true"))
	float MovingMultiplier = 2.0f;

protected:
	virtual void BeginPlay() override;
	virtual bool GunTrace(FHitResult& OutHit);
	virtual FVector GetDirectionFromStartToHit(const FVector& StartLocation, FHitResult HitResult) const;

	void ShowHitMarker();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Gun Info", meta = (AllowPrivateAccess = "true"))
	float MaxRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy", meta = (AllowPrivateAccess = "true"))
	float AccuracyRadius = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Ammo and Reloading", meta = (AllowPrivateAccess = "true"))
	uint8 MaxAmmo = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Impact", meta = (AllowPrivateAccess = "true"))
	float ImpulseForce = 100000.0f;

private:
	float FiringMultiplier = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Gun Info", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EGunType> GunType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Gun Info", meta = (AllowPrivateAccess = "true"))
	UTexture2D* GunTypeImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Gun Info", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ReticleWidgetClass;

	FTimerHandle ReloadTimerHandle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Ammo and Reloading", meta = (AllowPrivateAccess = "true"))
	float ReloadTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Base|Accuracy Multiplier", meta = (AllowPrivateAccess = "true"))
	float FiringMultiplierDecreaseRate = 5.0f;
}; 
