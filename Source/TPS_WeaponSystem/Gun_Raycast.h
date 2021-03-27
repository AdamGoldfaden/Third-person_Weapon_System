#pragma once

#include "CoreMinimal.h"
#include "Gun_Base.h"
#include "Gun_Raycast.generated.h"

UCLASS()
class TPS_WEAPONSYSTEM_API AGun_Raycast : public AGun_Base
{
	GENERATED_BODY()

public:
	virtual void StartShooting() override;
};
