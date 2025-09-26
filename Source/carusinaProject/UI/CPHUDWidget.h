// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API UCPHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCPHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void UpdateHealthBar(float NewCurrentHealth, float MaxHealth);

protected:
	UPROPERTY()
	TObjectPtr<class UCPHealthBarWidget> HealthBar;
};
