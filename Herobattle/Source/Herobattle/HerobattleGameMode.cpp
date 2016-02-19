// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Herobattle.h"
#include "HerobattleGameMode.h"
#include "HerobattleCharacter.h"
#include "HeroBattleHero.h"
#include "HBPlayerController.h"
#include "Skills/XMLSkillReader.h"
#include "UnrealNetwork.h"
#include "Engine.h"
#include "HBGameState.h"
#include "Base/Logging.h"

AHerobattleGameMode::AHerobattleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	//ConstructorHelpers::FClassFinder<UBaseSkillComponent> blub(TEXT("'class'Herobattle/Skills/Components/BaseSkillComponent.UBaseSkillComponent"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	blueHero_1 = nullptr;
	blueHero_2 = nullptr;
	blueHero_3 = nullptr;

	redHero_1 = nullptr;
	redHero_2 = nullptr;
	redHero_3 = nullptr;
}
void AHerobattleGameMode::PostLogin(APlayerController * NewPlayer)
{
	UWorld* world = GetWorld();
	AHBGameState* gameState = GetWorld()->GetGameState<AHBGameState>();
	logging = gameState->logging;
	Super::PostLogin(NewPlayer);
	if (HasAuthority())
	{
		AHBPlayerController* controller = (AHBPlayerController*) NewPlayer;
		if (m_PlayerCount == 0)
		{
			controller->ETeam = TeamColor::RED;
			
		}
		else
		{
			controller->ETeam = TeamColor::BLUE;
		}
		controller->m_Name.Append(TEXT("_")).AppendInt(m_PlayerCount);
		AHerobattleCharacter* character = (AHerobattleCharacter*)controller->GetPawn();
		if (character)
		{
			character->ETeam = controller->ETeam;
			character->m_Name = controller->m_Name;
			finishedPostLogin(NewPlayer);
		}
		m_PlayerCount++;
		FString name = TEXT("Gamemode: c++");
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, name);
	}
	
}

void AHerobattleGameMode::finishedPostLogin_Implementation(APlayerController * NewPlayer)
{

}

void AHerobattleGameMode::BeginPlay()
{
	if (HasAuthority())
	{
		XMLSkillReader* test = new XMLSkillReader();
		skillList = test->ReadXmlSkillFile(TEXT("Source/Herobattle/Definitions/Warrior.xml"), this);
	}
	Super::BeginPlay();
}

void AHerobattleGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (HasAuthority())
	{
		if (logging && logging->loggingOn)
		{
			logging->update(DeltaSeconds);
		}
		UpdateScore(DeltaSeconds);
	}
}

void AHerobattleGameMode::addShrine(uint8 pips, TeamColor team)
{
	if (HasAuthority())
	{
		if (team == TeamColor::BLUE)
		{
			m_BluePips += pips;
		}

		if (team == TeamColor::RED)
		{
			m_RedPips += pips;
		}
	}
}

void AHerobattleGameMode::removeShrine(uint8 pips, TeamColor team)
{
	if (HasAuthority())
	{
		if (team == TeamColor::BLUE)
		{
			m_BluePips -= pips;
			if (m_BluePips < 0)
			{
				m_BluePips = 0;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Blue Pips dropped bellow zero"));
			}

		}

		if (team == TeamColor::RED)
		{
			m_RedPips -= pips;
			if (m_RedPips < 0)
			{
				m_RedPips = 0;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Red Pips dropped bellow zero"));
			}

		}
	}
		
}

void AHerobattleGameMode::UpdateScore(float DeltaSeconds)
{
	float speed = 1.0f / CapturePointSpeed;

	AHBGameState* gameState = GetWorld()->GetGameState<AHBGameState>();
	gameState->RedScore += speed * m_RedPips  * DeltaSeconds;
	gameState->BlueScore += speed * m_BluePips  * DeltaSeconds;
}

void AHerobattleGameMode::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHerobattleGameMode, skillList);
	DOREPLIFETIME(AHerobattleGameMode, m_PlayerCount);
	DOREPLIFETIME(AHerobattleGameMode, BlueScore);
	DOREPLIFETIME(AHerobattleGameMode, RedScore);
}