#include "EnemyPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "PlayerCharacter.h"
#include "HealthBar.h"


AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Cast<UHealthBar>(HealthBar->GetWidget())->SetOwnerEnemyPawn(this);
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator HealthBarRotation = HealthBar->GetComponentRotation();
	FVector LookAtDirection = Player->GetActorLocation() - HealthBar->GetComponentLocation();
	HealthBarRotation.Yaw = LookAtDirection.Rotation().Yaw;
	HealthBar->SetWorldRotation(HealthBarRotation);
}

float AEnemyPawn::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bIsDead)
	{
		return 0.f;
	}

	Damage = FMath::Min(CurrentHealth, Damage);
	CurrentHealth -= Damage;
	
	if (CurrentHealth <= 0.f)
	{
		bIsDead = true;
		Die();
	}

	return Damage;
}

void AEnemyPawn::Die()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
