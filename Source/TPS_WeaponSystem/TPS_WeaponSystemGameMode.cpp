#include "TPS_WeaponSystemGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyPawn.h"
#include "Engine/StaticMeshActor.h"

void ATPS_WeaponSystemGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> EnemyActors;
	TArray<AActor*> PhysicsObjectActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyPawn::StaticClass(), EnemyActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), PhysicsObjectActors);
	
	for (AActor* Enemy : EnemyActors)
	{
		Enemies.Add(Cast<AEnemyPawn>(Enemy));
		EnemyTransforms.Add(Enemy->GetTransform());
	}

	for (AActor* PhysicsObject : PhysicsObjectActors)
	{
		PhysicsObjects.Add(Cast<AStaticMeshActor>(PhysicsObject));
		PhysicsObjectTransforms.Add(PhysicsObject->GetTransform());
	}
}

void ATPS_WeaponSystemGameMode::ResetLevel()
{
	for (int32 i = 0; i < Enemies.Num(); i++)
	{
		AEnemyPawn* Enemy = Enemies[i];
		Enemy->Revive();
		Enemy->SetActorTransform(EnemyTransforms[i]);	
	}
		
	for (int32 i = 0; i < PhysicsObjects.Num(); i++)
	{
		AStaticMeshActor* PhysicsObject = PhysicsObjects[i];
		PhysicsObject->SetActorTransform(PhysicsObjectTransforms[i]);
		PhysicsObject->GetStaticMeshComponent()->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
		PhysicsObject->GetStaticMeshComponent()->SetPhysicsAngularVelocity(FVector::ZeroVector);
	}
}