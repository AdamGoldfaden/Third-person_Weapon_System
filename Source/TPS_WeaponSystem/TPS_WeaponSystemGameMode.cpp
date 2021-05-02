#include "TPS_WeaponSystemGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyPawn.h"
#include "Engine/StaticMeshActor.h"

void ATPS_WeaponSystemGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyPawn::StaticClass(), Enemies);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), PhysicsObjects);
	
	for (AActor* Enemy : Enemies)
	{
		EnemyTransforms.Add(Enemy->GetTransform());
	}

	for (AActor* PhysicsObject : PhysicsObjects)
	{
		PhysicsObjectTransforms.Add(PhysicsObject->GetTransform());
	}
}

void ATPS_WeaponSystemGameMode::ResetLevel()
{
	for (int32 i = 0; i < Enemies.Num(); i++)
	{
		AEnemyPawn* Enemy = Cast<AEnemyPawn>(Enemies[i]);
		Enemy->Revive();
		Enemy->SetActorTransform(EnemyTransforms[i]);	}
		
	for (int32 i = 0; i < PhysicsObjects.Num(); i++)
	{
		AStaticMeshActor* PhysicsObject = Cast<AStaticMeshActor>(PhysicsObjects[i]);
		PhysicsObject->SetActorTransform(PhysicsObjectTransforms[i]);
		PhysicsObject->GetStaticMeshComponent()->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
		PhysicsObject->GetStaticMeshComponent()->SetPhysicsAngularVelocity(FVector::ZeroVector);
	}
}