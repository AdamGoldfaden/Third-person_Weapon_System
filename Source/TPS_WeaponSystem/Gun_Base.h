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
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	EGunType GunType;
	float MaxRange = 1000.f;

protected:
	virtual void BeginPlay() override;
	virtual bool GunTrace(FHitResult& OutHit);

public:	
	AGun_Base();
	virtual void Tick(float DeltaTime) override;
	virtual void StartShooting();
	virtual void StopShooting();
	virtual void Reload();

	AController* GetOwnerController() const;
	EGunType GetGunType() const;
};
