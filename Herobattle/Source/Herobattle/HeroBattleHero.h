// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Herobattle/Base/BaseCharacter.h"
#include "HeroBattleHero.generated.h"

UENUM(BlueprintType)
enum class HeroNumber : uint8
{
	HERO1, HERO2, HERO3
};

class AHerobattleGameMode;
UCLASS()
class HEROBATTLE_API AHeroBattleHero : public ABaseCharacter
{
	GENERATED_BODY()

public:


	// Sets default values for this character's properties
	AHeroBattleHero();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterProperties)
	HeroNumber heroNum;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = OnStart)
	void registerHeroToGameMode();

private:

	void setRedHero(AHerobattleGameMode* hbGamemode);

	void setBlueHero(AHerobattleGameMode* hbGamemode);



};
