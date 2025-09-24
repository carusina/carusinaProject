// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPWidgetComponent.h"
#include "CPUserWidget.h"

void UCPWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UCPUserWidget* CPUserWidget = Cast<UCPUserWidget>(GetWidget());
	if (CPUserWidget)
	{
		CPUserWidget->SetOwningActor(GetOwner());
	}
}
