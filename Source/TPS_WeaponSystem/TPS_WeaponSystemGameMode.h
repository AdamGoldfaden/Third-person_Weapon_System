#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPS_WeaponSystemGameMode.generated.h"

class AEnemyPawn;
class AStaticMeshActor;

UCLASS(minimalapi)
class ATPS_WeaponSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPS_WeaponSystemGameMode() {}
	void ResetLevel();

protected:
	virtual void BeginPlay() override;

private:
	TArray<AEnemyPawn*> Enemies;
	TArray<AStaticMeshActor*> PhysicsObjects;

	TArray<FTransform> EnemyTransforms;
	TArray<FTransform> PhysicsObjectTransforms;
};



