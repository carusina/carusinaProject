// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CPCharacterBase.h"
#include "CPCharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API ACPCharacterNonPlayer : public ACPCharacterBase
{
	GENERATED_BODY()

public:
	ACPCharacterNonPlayer();

protected:
	virtual void SetDead() override;
};
