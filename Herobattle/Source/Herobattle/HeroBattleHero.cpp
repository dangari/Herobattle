// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HeroBattleHero.h"
#include "HerobattleGameMode.h"


// Sets default values
AHeroBattleHero::AHeroBattleHero() : AHeroBattleHero::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	heroNum = HeroNumber::HERO1;
}

// Called when the game starts or when spawned
void AHeroBattleHero::BeginPlay()
{
	Super::BeginPlay();
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

void AHeroBattleHero::registerHeroToGameMode(AHeroBattleHero* hero)
{
	
	AHerobattleGameMode* hbGamemode = (AHerobattleGameMode*)AActor::GetWorld()->GetAuthGameMode();
	
	switch (ETeam)
	{
	case TeamColor::BLUE:
		setBlueHero(hbGamemode, hero);
		break;
	case TeamColor::RED:
		setRedHero(hbGamemode, hero);
		break;
	}
}


void AHeroBattleHero::setRedHero(AHerobattleGameMode* hbGamemode, AHeroBattleHero* hero)
{

}

void AHeroBattleHero::setBlueHero(AHerobattleGameMode* hbGamemode, AHeroBattleHero* hero)
{

}
