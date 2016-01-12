// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HBGameState.h"
#include "UnrealNetwork.h"




void AHBGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHBGameState, DebugSkillList);
}

