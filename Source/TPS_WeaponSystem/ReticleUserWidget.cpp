#include "ReticleUserWidget.h"
#include "Components/Image.h"
#include "PlayerCharacter.h"
#include "Gun_Base.h"
#include "GameFramework/CharacterMovementComponent.h"


void UReticleUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	
}
	

void UReticleUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	AGun_Base* OwnerCharacterGun;
	if (OwnerCharacter != nullptr)
	{
		OwnerCharacterGun = OwnerCharacter->GetGun();
	}
	else
	{
		return;
	}
	AccuracyMultiplier = OwnerCharacterGun->GetAccuracy();
	if (OwnerCharacter->bIsCrouched)
	{
		AccuracyMultiplier *= OwnerCharacterGun->CrouchMultiplier;
	}
	if (OwnerCharacter->GetIsAiming())
	{
		AccuracyMultiplier *= OwnerCharacterGun->AimingMultiplier;
	}
	if (OwnerCharacter->GetVelocity().SizeSquared() > 0.f)
	{
		AccuracyMultiplier *= OwnerCharacterGun->MovingMultiplier;
	}
	SetCrossHairPosition();
}

void UReticleUserWidget::SetCrossHairPosition()
{
	if (CrossHair_Bottom)
	{
		CrossHair_Bottom->SetRenderTranslation(FVector2D(0.f, AccuracyMultiplier*AccuracyTranslation));
	}

	if (CrossHair_Top)
	{
		CrossHair_Top->SetRenderTranslation(FVector2D(0.f, -AccuracyMultiplier*AccuracyTranslation));
	}

	if (CrossHair_Left)
	{
		CrossHair_Left->SetRenderTranslation(FVector2D(-AccuracyMultiplier*AccuracyTranslation, 0.f));
	}

	if (CrossHair_Right)
	{
		CrossHair_Right->SetRenderTranslation(FVector2D(AccuracyMultiplier*AccuracyTranslation, 0.f));
	}
}