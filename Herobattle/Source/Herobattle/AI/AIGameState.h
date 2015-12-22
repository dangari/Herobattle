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

	void UpdateAttackerNumber();

	TArray<FCharacterState> getAlliesCurrentAIState();

	TArray<FCharacterState> getAlliesOldAIState();

	TArray<FCharacterState> getEnemyCurrentAIState();

	TArray<FCharacterState> getEnemyOldAIState();

	FCharacterState getOwnerState();

	void addDeltaTime(float DeltaTime);

	AHeroBattleHero* getOwner();

	float m_deltaTime;

private:
	UPROPERTY()
	TArray<FCharacterState> AlliesCurrentAIState;

	UPROPERTY()
	TArray<FCharacterState> AlliesOldAIState;

	UPROPERTY()
	TArray<FCharacterState> EnemyCurrentAIState;

	UPROPERTY()
	TArray<FCharacterState> EnemyOldAIState;
	
	//Time since last newStateCall

	
	AHeroBattleHero* m_owner;
	FCharacterState m_ownerState;
};
