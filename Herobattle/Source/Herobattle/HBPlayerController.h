// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "HBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API AHBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHBPlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

	void LockCamera();
	void ReleaseCamera();
	virtual void SetupInputComponent() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);
private:
	bool bCameraIsLocked;
};
