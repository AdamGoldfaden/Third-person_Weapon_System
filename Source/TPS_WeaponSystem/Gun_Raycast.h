#pragma once

#include "CoreMinimal.h"
#include "Gun_Base.h"
#include "Gun_Raycast.generated.h"

UCLASS()
class TPS_WEAPONSYSTEM_API AGun_Raycast : public AGun_Base
{
	GENERATED_BODY()

private:
	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TimeBetweenShots = 0.1f;

	void FireBullet();

public:
	virtual void StartShooting() override;
	virtual void StopShooting() override;
};
