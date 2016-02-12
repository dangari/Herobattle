// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Herobattle/Base/BaseCharacter.h"
#include "HeroBattleHero.generated.h"

UENUM(BlueprintType)
enum class HeroState : uint8
{
	FLAGALL, FLAGSINGEL, NONE
};


DECLARE_LOG_CATEGORY_EXTERN(SkillLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HealthLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN( , Log, All);

class AHerobattleGameMode;
UCLASS()
class HEROBATTLE_API AHeroBattleHero : public ABaseCharacter
{
	GENERATED_BODY()

public:


	// Sets default values for this character's properties
	AHeroBattleHero();

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Flag)
	HeroState currentState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Flag)
	FVector singleFlagVectorLocation;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Flag)
	FVector allFlagVectorLocation;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = General)
	ABaseCharacter* owningPlayer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	
	

private:
	
};
