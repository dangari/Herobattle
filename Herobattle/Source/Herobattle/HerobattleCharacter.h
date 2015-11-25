// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Base/BaseCharacter.h"
#include "HerobattleCharacter.generated.h"

class AHeroBattleHero;
class AHBPlayerController;


UENUM(BlueprintType)
enum class SelectedFlag : uint8
{
	FLAGALL, FLAGG_ONE, FLAGG_TWO, FLAGG_THREE, NONE
};


UCLASS(config=Game)
class AHerobattleCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AHerobattleCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(BluePrintReadWrite, EditDefaultsOnly, Category = CamaraZoom)
	float fMinCameraRange;
	UPROPERTY(BluePrintReadWrite, EditDefaultsOnly, Category = CamaraZoom)
	float fMaxCameraRange;
	UPROPERTY(BluePrintReadWrite, EditDefaultsOnly, Category = CamaraZoom)
	float fStartRange;
	UPROPERTY(BluePrintReadWrite, EditDefaultsOnly, Category = CamaraZoom)
	float fCameraZoomSpeed;

	UFUNCTION(BlueprintCallable, Category = OnStart)
	void initializeMouse();

	UFUNCTION(BlueprintCallable, Category = OnStart)
	void addHero(uint8 index, AHeroBattleHero* hero);

	UFUNCTION(BlueprintCallable, Category = OnStart)
	AHeroBattleHero* getHero(uint8 index);
	
protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);



	void CameraZoom(float Value);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Input)
	void setController(AHBPlayerController* MyController);

	void setCameraLock(bool isLocked);


private:
	bool bCameraIsLocked;

	float fCurrentCameraRange;

	AHBPlayerController* MyController;

	UPROPERTY(Replicated)
	AHeroBattleHero* heroList[3];

	void startAttack();

	//interrupt skill and Stop autoattack
	void stopAllActions();
};

