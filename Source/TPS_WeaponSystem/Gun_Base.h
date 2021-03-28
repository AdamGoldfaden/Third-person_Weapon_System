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

	//UPROPERTY(EditAnywhere)
	EGunType GunType;

protected:
	UPROPERTY(EditAnywhere)
	float MaxRange = 10000.f;

	virtual void BeginPlay() override;
	virtual bool GunTrace(FHitResult& OutHit);
	virtual FVector GetTraceDirection(FHitResult HitResult);

public:	
	AGun_Base();
	virtual void Tick(float DeltaTime) override;
	virtual void StartShooting();
	virtual void StopShooting();
	virtual void Reload();

	AController* GetOwnerController() const;
	EGunType GetGunType() const;
	USkeletalMeshComponent* GetGunMesh() const;
}; 
