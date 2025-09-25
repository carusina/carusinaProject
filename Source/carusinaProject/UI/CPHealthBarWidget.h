// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPUserWidget.h"
#include "CPHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API UCPHealthBarWidget : public UCPUserWidget
{
	GENERATED_BODY()

public:
	UCPHealthBarWidget(const FObjectInitializer& ObjectInitializer);

	void UpdateHealthBar(float NewCurrentHealth, float MaxHealth);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HealthProgressBar;
};
