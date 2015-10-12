// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HBPlayerController.h"

AHBPlayerController::AHBPlayerController()
{
	
}

void AHBPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(true);
	InputMode.SetLockMouseToViewport(true);
	this->SetInputMode(InputMode);
	this->SetIgnoreLookInput(true);
	this->bShowMouseCursor = true;
	this->bEnableClickEvents = true;
	this->bEnableMouseOverEvents = true;
}

