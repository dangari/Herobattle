// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HeroBattleHero.h"
#include "HerobattleGameMode.h"
#include "UnrealNetwork.h"
#include "Engine.h"


DEFINE_LOG_CATEGORY(SkillLog);
DEFINE_LOG_CATEGORY(HealthLog);
DEFINE_LOG_CATEGORY(ManaLog);


// Sets default values
AHeroBattleHero::AHeroBattleHero() : AHeroBattleHero::ABaseCharacter()
{
	bReplicates = true;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	owningPlayer = nullptr;
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


void AHeroBattleHero::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHeroBattleHero, currentState);
	DOREPLIFETIME(AHeroBattleHero, singleFlagVectorLocation);
	DOREPLIFETIME(AHeroBattleHero, allFlagVectorLocation);
}
