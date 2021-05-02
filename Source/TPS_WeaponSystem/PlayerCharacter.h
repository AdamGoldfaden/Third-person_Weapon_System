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

public:	
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE AGun_Base* GetGun() const { return Gun; }
	UFUNCTION(BlueprintPure)
	bool GetIsAiming() const { return bIsAiming; }
	UFUNCTION(BlueprintPure)
	bool GetIsFiring() const { return bIsFiring; }

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

private:
	void StartShootingGun();
	void StopShootingGun();

	void StartAiming();
	void StopAiming();

	void StartCrouch();
	void StartUnCrouch();

	void SwitchGun(uint8 GunClassIndex);
	void SwitchToPreviousGun();
	void SwitchToNextGun();
	void ReloadGun();

	void SwitchToGun1();
	void SwitchToGun2();

	void CreateNewGun(uint8 GunClassIndex);

	void ResetLevel();

	float CapsuleWidth = 42.0f;
	float CapsuleHeight = 96.0f;
	float SpringArmStartZ;
	float AimingSpringArmStartZ;

	bool bIsAiming = false;
	bool bIsFiring = false;

	uint8 CurrentGunIndex;
	EGunType CurrentGunType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* AimingSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "APlayerCharacter|Aiming", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate = 45.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "APlayerCharacter|Aiming", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate = 45.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "APlayerCharacter|Aiming", meta = (AllowPrivateAccess = "true"))
	float AimingSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "APlayerCharacter|Crouch", meta = (AllowPrivateAccess = "true"))
	float SpringArmCrouchZ = 30.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "APlayerCharacter|Crouch", meta = (AllowPrivateAccess = "true"))
	float AimingSpringArmCrouchZ = 30.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "APlayerCharacter|Crouch", meta = (AllowPrivateAccess = "true"))
	float CrouchSpeed = 5.f;

	UPROPERTY()
	AGun_Base* Gun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "APlayerCharacter|GunTypes", meta = (AllowPrivateAccess = "true"))
	uint8 StartingGunIndex = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "APlayerCharacter|GunTypes", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AGun_Base>> GunClasses;

	
};
