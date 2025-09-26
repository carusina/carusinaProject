// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPHUDWidget.h"
#include "CPHealthBarWidget.h"
#include "Interface/CPCharacterHUDInterface.h"

UCPHUDWidget::UCPHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCPHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar = Cast<UCPHealthBarWidget>(GetWidgetFromName(TEXT("WBP_Health")));
	ensure(HealthBar);

	ICPCharacterHUDInterface* HUDPawn = Cast<ICPCharacterHUDInterface>(GetOwningPlayerPawn());
	if (HUDPawn)
	{
		HUDPawn->SetupHUDWidget(this);
	}
}

void UCPHUDWidget::UpdateHealthBar(float NewCurrentHealth, float MaxHealth)
{
	HealthBar->UpdateHealthBar(NewCurrentHealth, MaxHealth);
}
