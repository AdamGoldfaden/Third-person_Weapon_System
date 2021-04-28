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

	if (!OwnerCharacter)
	{
		return;
	}

	AGun_Base* OwnerCharacterGun = OwnerCharacter->GetGun();

	//TODO: Change get Accuracy to include all this
	AccuracyMultiplier = OwnerCharacterGun->GetAccuracyMultiplier();
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