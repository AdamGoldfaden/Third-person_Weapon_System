#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gun_Base.h"

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

	Gun = GetWorld()->SpawnActor<AGun_Base>(StartingGunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	CurrentGunType = Gun->GetGunType();
	PreviousGunType = CurrentGunType;
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
	if (GunClassIndex == CurrentGunType) { return; }

	PreviousGunType = CurrentGunType;

	AGun_Base* TempGun = Gun;
	Gun = nullptr;
	TempGun->Destroy();

	Gun = GetWorld()->SpawnActor<AGun_Base>(GunClasses[GunClassIndex]);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	CurrentGunType = Gun->GetGunType();
}

void APlayerCharacter::SwitchToPreviousGun()
{
	SwitchGun(PreviousGunType);
}

void APlayerCharacter::ReloadRun()
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
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::ReloadRun);
	PlayerInputComponent->BindAction("SwitchToPreviousGun", IE_Pressed, this, &APlayerCharacter::SwitchToPreviousGun);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::StartUnCrouch);
	PlayerInputComponent->BindAction("SwitchToGun1", IE_Pressed, this, &APlayerCharacter::SwitchToGun1);
	PlayerInputComponent->BindAction("SwitchToGun2", IE_Pressed, this, &APlayerCharacter::SwitchToGun2);

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
		FRotator YawRotation(0, Rotation.Yaw, 0);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator& Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);

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