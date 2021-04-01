#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AGun_Base;
class USpringArmComponent;
class UCameraComponent;
enum EGunType;

UCLASS()
class TPS_WEAPONSYSTEM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	float CapsuleWidth = 42.0f;
	float CapsuleHeight = 96.0f;
	float SpringArmStartZ;
	float AimingSpringArmStartZ;

	bool bIsAiming = false;
	EGunType PreviousGunType;
	EGunType CurrentGunType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate = 45.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate = 45.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AimingSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpringArmCrouchZ = 30.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AimingSpringArmCrouchZ = 30.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CrouchSpeed = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun_Base> StartingGunClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* AimingSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY()
	AGun_Base* Gun;

	void StartShootingGun();
	void StopShootingGun();

	void StartAiming();
	void StopAiming();

	void StartCrouch();
	void StartUnCrouch();

	void SwitchGun(EGunType GunType);
	void SwitchToPreviousGun();
	void ReloadRun();

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

public:	
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION(BlueprintPure)
	bool GetIsAiming() const { return bIsAiming; }
};
