#include "AccuracyReticleUserWidger.h"
#include "Components/Image.h"
#include "PlayerCharacter.h"
#include "Gun_Base.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAccuracyReticleUserWidger::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!GetOwnerCharacter())
	{
		return;
	}

	AGun_Base* OwnerCharacterGun = GetOwnerCharacter()->GetGun();
	if (!OwnerCharacterGun)
	{
		return;
	}

	AccuracyMultiplier = OwnerCharacterGun->GetAccuracyMultiplier();
	SetCrossHairPosition();
}

void UAccuracyReticleUserWidger::SetCrossHairPosition()
{
	if (CrossHair_Bottom)
	{
		CrossHair_Bottom->SetRenderTranslation(FVector2D(0.f, AccuracyMultiplier * AccuracyTranslation));
	}

	if (CrossHair_Top)
	{
		CrossHair_Top->SetRenderTranslation(FVector2D(0.f, -AccuracyMultiplier * AccuracyTranslation));
	}

	if (CrossHair_Left)
	{
		CrossHair_Left->SetRenderTranslation(FVector2D(-AccuracyMultiplier * AccuracyTranslation, 0.f));
	}

	if (CrossHair_Right)
	{
		CrossHair_Right->SetRenderTranslation(FVector2D(AccuracyMultiplier * AccuracyTranslation, 0.f));
	}
}