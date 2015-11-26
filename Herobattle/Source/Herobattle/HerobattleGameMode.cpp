// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Herobattle.h"
#include "HerobattleGameMode.h"
#include "HerobattleCharacter.h"
#include "HeroBattleHero.h"
#include "HBPlayerController.h"
#include "Skills/XMLSkillReader.h"
#include "UnrealNetwork.h"

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
		ABaseCharacter* character = (ABaseCharacter*)controller->GetControlledPawn();
		if (character)
		{
			character->ETeam = controller->ETeam;
		}
	}
}

void AHerobattleGameMode::BeginPlay()
{
	if (HasAuthority())
	{
		XMLSkillReader* test = new XMLSkillReader();
		skillList = test->ReadXmlSkillFile(TEXT("Source/Herobattle/Definitions/skill.xml"));
	}
}

void AHerobattleGameMode::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHerobattleGameMode, skillList);
	DOREPLIFETIME(AHerobattleGameMode, m_PlayerCount);
}