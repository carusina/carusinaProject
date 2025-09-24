// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHealthZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float /* Current Hp */);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARUSINAPROJECT_API UCPCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPCharacterStatComponent();

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	float ApplyDamage(float DamageAmount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetCurrentHealth(const float NewHealth);

public:
	FOnHealthZeroDelegate OnHealthZero;
	FOnHealthChangedDelegate OnHealthChanged;
	
protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Stat|Health")
	float MaxHealth;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat|Health")
	float CurrentHealth;

};
