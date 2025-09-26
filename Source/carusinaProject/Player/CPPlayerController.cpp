// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Character/CPCharacterPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/CPHUDWidget.h"

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

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FXCursorRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/carusinaProject/Input/Cursor/FX_Cursor.FX_Cursor'"));
	if (FXCursorRef.Object)
	{
		FXCursor = FXCursorRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> BasicAttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/carusinaProject/Input/Actions/IA_BasicAttack.IA_BasicAttack'"));
	if (BasicAttackActionRef.Object)
	{
		BasicAttackAction = BasicAttackActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> DodgeActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/carusinaProject/Input/Actions/IA_DodgeAction.IA_DodgeAction'"));
	if (DodgeActionRef.Object)
	{
		DodgeAction = DodgeActionRef.Object;
	}

	static ConstructorHelpers::FClassFinder<UCPHUDWidget> CPHUDWidgetRef(TEXT("/Game/carusinaProject/UI/WBP_HUD.WBP_HUD_C"));
	if (CPHUDWidgetRef.Class)
	{
		CPHUDWidgetClass = CPHUDWidgetRef.Class;
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

	ControlledCharacter = CastChecked<ACPCharacterPlayer>(GetPawn());
	
	CPHUDWidget = CreateWidget<UCPHUDWidget>(this, CPHUDWidgetClass);
	if (CPHUDWidget)
	{
		UE_LOG(LogTemp, Log, TEXT("HUD Widget created"));
		CPHUDWidget->AddToViewport();
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
	
	EnhancedInputComponent->BindAction(BasicAttackAction, ETriggerEvent::Triggered, this, &ACPPlayerController::BasicAttack);
	EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ACPPlayerController::Dodge);
}

void ACPPlayerController::GetLocationUnderCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	if (HitResult.bBlockingHit)
	{
		GoalLocation = HitResult.Location;
		const FVector ControlledCharacterLocation = ControlledCharacter->GetActorLocation();
		FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(ControlledCharacterLocation, GoalLocation);

		ControlledCharacter->AddMovementInput(Direction, 1.0, false);
	}
}

void ACPPlayerController::MoveToLocation()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, GoalLocation);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FXCursor, GoalLocation);
}

void ACPPlayerController::BasicAttack()
{
	ControlledCharacter->ProcessBasicAttack();
}

void ACPPlayerController::Dodge()
{
	ControlledCharacter->ProcessDodge();
}
