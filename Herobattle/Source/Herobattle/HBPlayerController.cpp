// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HBPlayerController.h"
#include "HerobattleCharacter.h"
#include "Engine.h"
#include "UnrealNetwork.h"

AHBPlayerController::AHBPlayerController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bCameraIsLocked = false;

	SetIgnoreLookInput(true);
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AHBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(true);
	InputMode.SetLockMouseToViewport(true);
	SetInputMode(InputMode);
	SetIgnoreLookInput(true);
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	AHerobattleCharacter* currentPlayer = (AHerobattleCharacter*)GetPawn();
	if (currentPlayer)
	{
		currentPlayer->setController(this);
	}
}

void AHBPlayerController::LockCamera()
{
	SetIgnoreLookInput(false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LockCamera"));

	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
	AHerobattleCharacter* currentPlayer = (AHerobattleCharacter*)GetPawn();
	if (currentPlayer)
	{
		currentPlayer->setCameraLock(true);
	}
}

void AHBPlayerController::ReleaseCamera()
{
	SetIgnoreLookInput(true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ReleaseCamera"));
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	AHerobattleCharacter* currentPlayer = (AHerobattleCharacter*)GetPawn();
	if (currentPlayer)
	{
		currentPlayer->setCameraLock(false);
	}
}

void AHBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("RightMouse", IE_Pressed, this, &AHBPlayerController::LockCamera);
	InputComponent->BindAction("RightMouse", IE_Released, this, &AHBPlayerController::ReleaseCamera);
}


void AHBPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHBPlayerController, ETeam);
}

