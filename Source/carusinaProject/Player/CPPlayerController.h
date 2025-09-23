// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NiagaraFunctionLibrary.h"
#include "CPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARUSINAPROJECT_API ACPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPPlayerController();

protected:
	virtual void BeginPlay() override;

	// Player Input Section
	virtual void SetupInputComponent() override;

private:
	// Player Input Section
	void GetLocationUnderCursor();
	void MoveToLocation();
	
protected:
	// Player Input Section
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SetDestinationAction;

private:
	// Player Input Section
	FVector GoalLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> FXCursor;
};
