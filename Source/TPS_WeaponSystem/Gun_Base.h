#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun_Base.generated.h"

UENUM(BlueprintType)
enum EGunType
{
	Raycast UMETA(DisplayName, "Raycast"),
	Projectile UMETA(DisplayName, "Projectile")
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EGunType> GunType;

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxRange = 10000.f;

	virtual bool GunTrace(FHitResult& OutHit);
	virtual FVector GetDirectionFromStartToHit(FVector StartLocation, FHitResult HitResult) const;

public:	
	AGun_Base();
	virtual void StartShooting(){}
	virtual void StopShooting(){}
	virtual void Reload(){}

	AController* GetOwnerController() const;
	FORCEINLINE EGunType GetGunType() const { return GunType; };
	FORCEINLINE USkeletalMeshComponent* GetGunMesh() const { return Mesh; };
}; 
