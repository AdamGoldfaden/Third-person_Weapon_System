#pragma once

#include "CoreMinimal.h"
#include "Gun_Base.h"
#include "Gun_Raycast.generated.h"

UCLASS()
class TPS_WEAPONSYSTEM_API AGun_Raycast : public AGun_Base
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void StartShooting() override;
	virtual void StopShooting() override;

private:
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|FireRate", meta = (AllowPrivateAccess = "true"))
	float TimeBetweenShots = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|FireRate", meta = (AllowPrivateAccess = "true"))
	float FiringAccuracyMultipler = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|Recoil", meta = (AllowPrivateAccess = "true"))
	float VerticalRecoilAmount = 0.15f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|Recoil", meta = (AllowPrivateAccess = "true"))
	float HorizontalRecoilAmount = 0.02f;;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|Recoil",  meta = (AllowPrivateAccess = "true"))
	float RecoilSpeed = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|VFX", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|VFX", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|VFX", meta = (AllowPrivateAccess = "true"))
	float MuzzleFlashScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun_Raycast|VFX", meta = (AllowPrivateAccess = "true"))
	float ImpactEffectScale;

	void FireBullet();
};
