#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gun_Base.h"
#include "TPSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TPS_WeaponSystemGameMode.h"



APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(CapsuleWidth, CapsuleHeight);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Default SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	AimingSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Aiming SpringArm"));
	AimingSpringArm->SetupAttachment(RootComponent);
	AimingSpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpringArmStartZ = SpringArm->GetRelativeLocation().Z;
	AimingSpringArmStartZ = AimingSpringArm->GetRelativeLocation().Z;

	CreateNewGun(StartingGunIndex);
}

void APlayerCharacter::StartShootingGun()
{
	Gun->StartShooting();
	bIsFiring = true;
}

void APlayerCharacter::StopShootingGun()
{
	Gun->StopShooting();
	bIsFiring = false;
}

void APlayerCharacter::StartAiming()
{
	bIsAiming = true;
	Camera->AttachToComponent(AimingSpringArm, FAttachmentTransformRules::KeepWorldTransform, USpringArmComponent::SocketName);
}

void APlayerCharacter::StopAiming()
{
	bIsAiming = false;
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepWorldTransform, USpringArmComponent::SocketName);
}

void APlayerCharacter::SwitchGun(uint8 GunClassIndex)
{
	if (GunClassIndex == CurrentGunType) 
	{ 
		return; 
	}

	Gun->Destroy();

	CreateNewGun(GunClassIndex);


}

void APlayerCharacter::SwitchToPreviousGun()
{
	CurrentGunIndex = --CurrentGunIndex % GunClasses.Num();
	SwitchGun(CurrentGunIndex);
}

void APlayerCharacter::SwitchToNextGun()
{
	CurrentGunIndex = ++CurrentGunIndex % GunClasses.Num();
	SwitchGun(CurrentGunIndex);
}

void APlayerCharacter::ReloadGun()
{
	Gun->Reload();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Camera->SetRelativeLocation(FMath::VInterpTo(Camera->GetRelativeLocation(), FVector(0.f,0.f,0.f), DeltaTime, AimingSpeed));

	if (bIsCrouched)
	{
		float SpringArmZ = FMath::FInterpTo(SpringArm->GetRelativeLocation().Z, SpringArmCrouchZ, DeltaTime, CrouchSpeed);
		float AimingSpringArmZ = FMath::FInterpTo(AimingSpringArm->GetRelativeLocation().Z, AimingSpringArmCrouchZ, 
			DeltaTime, CrouchSpeed);
		SpringArm->SetRelativeLocation(FVector(0, 0, SpringArmZ));
		AimingSpringArm->SetRelativeLocation(FVector(0, 0, AimingSpringArmZ));
	}
	else
	{
		float SpringArmZ = FMath::FInterpTo(SpringArm->GetRelativeLocation().Z, SpringArmStartZ, DeltaTime, CrouchSpeed);
		float AimingSpringArmZ = FMath::FInterpTo(AimingSpringArm->GetRelativeLocation().Z, AimingSpringArmStartZ, 
			DeltaTime, CrouchSpeed);
		SpringArm->SetRelativeLocation(FVector(0, 0, SpringArmZ));
		AimingSpringArm->SetRelativeLocation(FVector(0, 0, AimingSpringArmZ));
	}
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	check(PlayerInputComponent);
	
	//Action mappings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::StartShootingGun);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerCharacter::StopShootingGun);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &APlayerCharacter::StartAiming);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &APlayerCharacter::StopAiming);
	PlayerInputComponent->BindAction("ReloadGun", IE_Pressed, this, &APlayerCharacter::ReloadGun);
	PlayerInputComponent->BindAction("SwitchToPreviousGun", IE_Pressed, this, &APlayerCharacter::SwitchToPreviousGun);
	PlayerInputComponent->BindAction("SwitchToNextGun", IE_Pressed, this, &APlayerCharacter::SwitchToNextGun);
	PlayerInputComponent->BindAction("SwitchToGun1", IE_Pressed, this, &APlayerCharacter::SwitchToGun1);
	PlayerInputComponent->BindAction("SwitchToGun2", IE_Pressed, this, &APlayerCharacter::SwitchToGun2);
	PlayerInputComponent->BindAction("SwitchToGun3", IE_Pressed, this, &APlayerCharacter::SwitchToGun3);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::StartUnCrouch);
	PlayerInputComponent->BindAction("ResetLevel", IE_Pressed, this, &APlayerCharacter::ResetLevel);

	//Axis mappings
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator& Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator& Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::StartCrouch()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		Crouch();
	}
}

void APlayerCharacter::StartUnCrouch()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		UnCrouch();
	}
}

void APlayerCharacter::SwitchToGun1()
{
	SwitchGun(0);
}

void APlayerCharacter::SwitchToGun2()
{
	SwitchGun(1);
}

void APlayerCharacter::SwitchToGun3()
{
	SwitchGun(2);
}

void APlayerCharacter::CreateNewGun(uint8 GunClassIndex) 
{
	Gun = GetWorld()->SpawnActor<AGun_Base>(GunClasses[GunClassIndex % GunClasses.Num()]);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	Cast<ATPSPlayerController>(GetController())->ChangeReticle(Gun->GetReticleWidgetClass());

	CurrentGunType = Gun->GetGunType();
	CurrentGunIndex = GunClassIndex;
}

void APlayerCharacter::ResetLevel()
{
	if (ATPS_WeaponSystemGameMode* GameMode = Cast<ATPS_WeaponSystemGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->ResetLevel();
	}
}