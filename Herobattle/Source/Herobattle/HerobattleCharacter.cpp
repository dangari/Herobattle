// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Herobattle.h"
#include "HerobattleCharacter.h"
#include "Engine.h"
#include "HBPlayerController.h"
#include "UnrealNetwork.h"
#include "HeroBattleHero.h"

//////////////////////////////////////////////////////////////////////////
// AHerobattleCharacter

AHerobattleCharacter::AHerobattleCharacter() :AHerobattleCharacter::ABaseCharacter()
{
	bReplicates = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bCameraIsLocked = false;
	fStartRange = 600.0f;
	fMinCameraRange = 150.0f;
	fMaxCameraRange = 600.0f;
	fCurrentCameraRange = fStartRange;
	fCameraZoomSpeed = 50.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = fCurrentCameraRange; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	
}

//////////////////////////////////////////////////////////////////////////
// Input
void AHerobattleCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	

	// Set up gameplay key bindings
	check(InputComponent);
	
	InputComponent->BindAction("TestButton", IE_Released, this, &AHerobattleCharacter::initializeMouse);
	InputComponent->BindAction("Attack", IE_Released, this, &AHerobattleCharacter::startAttack);
	InputComponent->BindAction("Stop", IE_Released, this, &AHerobattleCharacter::stopAllActions);


	InputComponent->BindAxis("MoveForward", this, &AHerobattleCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHerobattleCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AHerobattleCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AHerobattleCharacter::LookUpAtRate);



	// Handle Camera Zoom
	InputComponent->BindAxis("MWheeel", this, &AHerobattleCharacter::CameraZoom);

}

void AHerobattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (Controller && Controller->IsLocalPlayerController())
	{
		//initializeMouse();
	}
}




void AHerobattleCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());


}

void AHerobattleCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHerobattleCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !(isCastingSkill()))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}
}

void AHerobattleCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !(isCastingSkill()))
	{
		if (bCameraIsLocked){
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
		else {
			float deltaRot = Value * 2 * BaseTurnRate * GetWorld()->GetDeltaSeconds();
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Yaw += deltaRot;
			Controller->SetControlRotation(Rotation);
			GetMesh()->AddRelativeRotation(FRotator(0.0f, deltaRot, 0.0f));
			/*float meshYaw = GetMesh()->GetRelativeTransform().Rotator().Yaw;
			Controller->SetControlRotation(Rotation);*/
		}
	}
}



void AHerobattleCharacter::CameraZoom(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f)){
		fCurrentCameraRange -= Value * fCameraZoomSpeed;
		if (fCurrentCameraRange > fMaxCameraRange)
			fCurrentCameraRange = fMaxCameraRange;
		else if (fCurrentCameraRange < fMinCameraRange)
			fCurrentCameraRange = fMinCameraRange;
		CameraBoom->TargetArmLength = fCurrentCameraRange;
	}

}

void AHerobattleCharacter::initializeMouse()
{
	//MyController = Cast<APlayerController>(Controller);
	MyController =  (AHBPlayerController*)GetWorld()->GetFirstPlayerController();
	//Input Mode for hiding courser
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(true);
	InputMode.SetLockMouseToViewport(true);
	MyController->SetInputMode(InputMode);
	MyController->SetIgnoreLookInput(true);
	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;
	MyController->bEnableMouseOverEvents = true;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MouseInit"));

}


void AHerobattleCharacter::addHero(uint8 index, AHeroBattleHero* hero)
{
	if (index < 3)
	{
		heroList[index] = hero;
	}
}


AHeroBattleHero* AHerobattleCharacter::getHero(uint8 index)
{
	if (index < 3)
	{
		return heroList[index];
	}
	return nullptr;
}

void AHerobattleCharacter::updateTeamColor()
{
	for (auto& hero : heroList)
	{
		hero->ETeam = ETeam;
	}
}

void AHerobattleCharacter::setController(AHBPlayerController* MyController)
{
	MyController = MyController;
}

void AHerobattleCharacter::setCameraLock(bool isLocked)
{
	bCameraIsLocked = isLocked;
}


void AHerobattleCharacter::startAttack()
{
	setAttack(true);
}

void AHerobattleCharacter::stopAllActions()
{
	setAttack(false);
	stopCurrenSkill();
}

void AHerobattleCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHerobattleCharacter, heroList);
	DOREPLIFETIME(AHerobattleCharacter, ETeam);
}