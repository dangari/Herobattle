// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HBGameState.h"
#include "UnrealNetwork.h"
#include "Base/Logging.h"




void AHBGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHBGameState, DebugSkillList);
	DOREPLIFETIME(AHBGameState, BlueScore);
	DOREPLIFETIME(AHBGameState, RedScore);
}

AHBGameState::AHBGameState()
	:RedScore(0)
	, BlueScore(0)
{
	
}

AHBGameState::~AHBGameState()
{

}

void AHBGameState::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority() && !logging)
		logging = NewObject<ULogging>(this);
}

