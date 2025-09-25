// Fill out your copyright notice in the Description page of Project Settings.


#include "CPCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "CharacterStat/CPCharacterStatComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACPCharacterPlayer::ACPCharacterPlayer()
{
	// Camera Section
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1400.0f;
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetWorldRotation(FRotator(-50.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 55.0f;
}

void ACPCharacterPlayer::GainExperience(float Amount)
{
	CurrentExperience += Amount;
	if (CurrentExperience >= Stat->GetBaseStat().RequiredExperience)
	{
		CurrentExperience -= Stat->GetBaseStat().RequiredExperience;
		
		Stat->SetLevel(Stat->GetCurrentLevel() + 1);
		GainExperience(0.0f);
	}
}
