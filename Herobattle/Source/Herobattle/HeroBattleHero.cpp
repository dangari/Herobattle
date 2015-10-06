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

void AHeroBattleHero::registerHeroToGameMode()
{
	
	AHerobattleGameMode* hbGamemode = (AHerobattleGameMode*)AActor::GetWorld()->GetAuthGameMode();
	
	switch (ETeam)
	{
	case TeamColor::BLUE:
		setBlueHero(hbGamemode);
		break;
	case TeamColor::RED:
		setRedHero(hbGamemode);
		break;
	}
}


void AHeroBattleHero::setRedHero(AHerobattleGameMode* hbGamemode)
{
	switch (heroNum)
	{
	case HeroNumber::HERO1:
		hbGamemode->redHero_1 = this;
		break;
	case HeroNumber::HERO2:
		hbGamemode->redHero_2 = this;
		break;
	case HeroNumber::HERO3:
		hbGamemode->redHero_3 = this;
		break;
	}
}

void AHeroBattleHero::setBlueHero(AHerobattleGameMode* hbGamemode)
{
	switch (heroNum)
	{
	case HeroNumber::HERO1:
		hbGamemode->blueHero_1 = this;
		break;
	case HeroNumber::HERO2:
		hbGamemode->blueHero_2 = this;
		break;
	case HeroNumber::HERO3:
		hbGamemode->blueHero_3 = this;
		break;
	}
}
