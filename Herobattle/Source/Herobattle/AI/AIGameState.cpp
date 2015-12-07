// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "AIGameState.h"
#include "Base/BaseCharacter.h"
#include "HeroBattleHero.h"




UAIGameState::UAIGameState()
{

}

UAIGameState::~UAIGameState()
{

}

void UAIGameState::newState(ABaseCharacter* owner)
{
	m_owner = Cast<AHeroBattleHero>(owner);
	EnemyOldAIState = EnemyCurrentAIState;
	TArray<FCharacterState> newEnemyState;
	EnemyCurrentAIState = newEnemyState;
	
	EnemyOldAIState = AlliesCurrentAIState;
	TArray<FCharacterState> newAlliesState;
	AlliesCurrentAIState = newEnemyState;

	m_deltaTime = 0.0f;
}

void UAIGameState::addCharacterState(FCharacterState state)
{
	if (state.ETeam != m_owner->ETeam)
	{
		EnemyCurrentAIState.Add(state);
	}
	else
	{
		AlliesCurrentAIState.Add(state);
	}
}

TArray<FCharacterState> UAIGameState::getAlliesCurrentAIState()
{
	return AlliesCurrentAIState;
}

TArray<FCharacterState> UAIGameState::getAlliesOldAIState()
{
	return AlliesOldAIState;
}

TArray<FCharacterState> UAIGameState::getEnemyCurrentAIState()
{
	return EnemyCurrentAIState;
}

TArray<FCharacterState> UAIGameState::getEnemyOldAIState()
{
	return EnemyCurrentAIState;
}

void UAIGameState::addDeltaTime(float DeltaTime)
{
	m_deltaTime += DeltaTime;
}

AHeroBattleHero* UAIGameState::getOwner()
{
	return m_owner;
}
