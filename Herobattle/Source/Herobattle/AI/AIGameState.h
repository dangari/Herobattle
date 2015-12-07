// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "CharacterState.h"
#include "AIGameState.generated.h"


class ABaseCharacter;
class AHeroBattleHero;

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UAIGameState : public UObject
{
	GENERATED_BODY()

public:

	UAIGameState();
	~UAIGameState();

	//sets the currentAIStae to oldAIState
	void newState(ABaseCharacter* owner);

	//adds a characterState to currentAiState
	void addCharacterState(FCharacterState state);

	TArray<FCharacterState> getAlliesCurrentAIState();

	TArray<FCharacterState> getAlliesOldAIState();

	TArray<FCharacterState> getEnemyCurrentAIState();

	TArray<FCharacterState> getEnemyOldAIState();

	void addDeltaTime(float DeltaTime);

	AHeroBattleHero* getOwner();

	float m_deltaTime;

private:
	TArray<FCharacterState> AlliesCurrentAIState;
	TArray<FCharacterState> AlliesOldAIState;

	TArray<FCharacterState> EnemyCurrentAIState;
	TArray<FCharacterState> EnemyOldAIState;
	
	//Time since last newStateCall

	
	AHeroBattleHero* m_owner;
};
