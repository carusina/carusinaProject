// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPCharacterBase.h"
#include "Interface/CPCharacterHUDInterface.h"
#include "CPCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API ACPCharacterPlayer : public ACPCharacterBase, public ICPCharacterHUDInterface
{
	GENERATED_BODY()

public:
	ACPCharacterPlayer();

public:
	void GainExperience(float Amount);

protected:
	virtual void SetupHUDWidget(class UCPHUDWidget* InHUDWidgetPtr) override;
	
protected:
	// Camera Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	// Experience
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Experience")
	float CurrentExperience;
};
