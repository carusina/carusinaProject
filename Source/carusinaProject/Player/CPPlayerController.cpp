// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ACPPlayerController::ACPPlayerController()
{
	// Player Input Section
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/carusinaProject/Input/IMC_Default.IMC_Default'"));
	if (DefaultMappingContextRef.Object)
	{
		DefaultMappingContext = DefaultMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SetDestinationActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/carusinaProject/Input/Actions/IA_SetDestination.IA_SetDestination'"));
	if (SetDestinationActionRef.Object)
	{
		SetDestinationAction = SetDestinationActionRef.Object;
	}
}

void ACPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetShowMouseCursor(true);

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMappingContext)
			{
				InputSystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ACPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(SetDestinationAction, ETriggerEvent::Triggered, this, &ACPPlayerController::GetLocationUnderCursor);
	EnhancedInputComponent->BindAction(SetDestinationAction, ETriggerEvent::Started, this, &AController::StopMovement);
	EnhancedInputComponent->BindAction(SetDestinationAction, ETriggerEvent::Canceled, this, &ACPPlayerController::MoveToLocation);
	EnhancedInputComponent->BindAction(SetDestinationAction, ETriggerEvent::Completed, this, &ACPPlayerController::MoveToLocation);
}

void ACPPlayerController::GetLocationUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	if (HitResult.bBlockingHit)
	{
		GoalLocation = HitResult.Location;
		APawn* ControlledPawn = GetPawn();
		const FVector ControlledPawnLocation = ControlledPawn->GetActorLocation();
		FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(ControlledPawnLocation, GoalLocation);

		ControlledPawn->AddMovementInput(Direction, 1.0, false);
	}
	
}

void ACPPlayerController::MoveToLocation()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, GoalLocation);
}
