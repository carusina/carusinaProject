// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPHealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/CPCharacterWidgetInterface.h"

UCPHealthBarWidget::UCPHealthBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHealth = -1.0f;
}

void UCPHealthBarWidget::UpdateHealthBar(float NewCurrentHealth)
{
	ensure(MaxHealth > 0.0f);

	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(NewCurrentHealth / MaxHealth);
	}
}

void UCPHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HealthProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HealthBar")));
	ensure(HealthProgressBar);

	ICPCharacterWidgetInterface* CharacterWidget = Cast<ICPCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}
