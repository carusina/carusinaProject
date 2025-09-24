// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/CPCharacterStatComponent.h"

// Sets default values for this component's properties
UCPCharacterStatComponent::UCPCharacterStatComponent()
{
	MaxHealth = 100.0f;
}


float UCPCharacterStatComponent::ApplyDamage(float DamageAmount)
{
	SetCurrentHealth(CurrentHealth - DamageAmount);
	if (CurrentHealth <= KINDA_SMALL_NUMBER /* 1e-4f */)
	{
		OnHealthZero.Broadcast();
	}
	
	return DamageAmount;
}

// Called when the game starts
void UCPCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UCPCharacterStatComponent::SetCurrentHealth(const float NewHealth)
{
	CurrentHealth = FMath::Clamp<float>(NewHealth, 0, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}
