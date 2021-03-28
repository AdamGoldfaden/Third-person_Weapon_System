#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class AGun_Base;
enum EGunType;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TPS_WEAPONSYSTEM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	bool bIsAiming = false;
	EGunType PreviousGunType;
	EGunType CurrentGunType;

	UPROPERTY(EditAnywhere)
	float AimingSpeed = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* AimingSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun_Base> StartingGunClass;
	UPROPERTY()
	AGun_Base* Gun;

	void StartShootingGun();
	void StopShootingGun();

	void StartAiming();
	void StopAiming();

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
	
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION(BlueprintPure)
	bool GetIsAiming() const { return bIsAiming; }

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;
};
