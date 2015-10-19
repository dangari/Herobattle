// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HeroBattleHero.h"
#include "HerobattleGameMode.h"


// Sets default values
AHeroBattleHero::AHeroBattleHero() : AHeroBattleHero::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentState = HeroState::NONE;
}

// Called when the game starts or when spawned
void AHeroBattleHero::BeginPlay()
{
	Super::BeginPlay();
	//registerHeroToGameMode();
}

// Called every frame
void AHeroBattleHero::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AHeroBattleHero::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

