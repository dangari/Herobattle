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

	void newStateSim(UAISimCharacter* owner);
	//adds a characterState to currentAiState
	void addCharacterState(FCharacterState state);

	void UpdateAttackerNumber();

	void replaceState(FCharacterState state);

	void createSimCharacters();

	TArray<FCharacterState> getAlliesCurrentAIState();

	TArray<FCharacterState> getAlliesOldAIState();

	TArray<FCharacterState> getEnemyCurrentAIState();

	TArray<FCharacterState> getEnemyOldAIState();

	TMap<FString, FCharacterState> getCharacterList();

	TMap<FString, ABaseCharacter*> getCharacterInstanceList();

	FCharacterState getOwnerState();

	UAIGameState* simulate(float DeltaTime);

	void addDeltaTime(float DeltaTime);

	AHeroBattleHero* getOwner();

	float m_deltaTime;

	UAIGameState* copy();


	void simulateCharacter(float DeltaTime, TArray<FCharacterState> stateList, UAIGameState* gameState);
	void setSimOwner(UAISimCharacter* character);
	UAISimCharacter* getSimOwner();
	UPROPERTY()
	TArray<FCharacterState> AlliesCurrentAIState;

	UPROPERTY()
	TArray<FCharacterState> AlliesOldAIState;

	UPROPERTY()
	TArray<FCharacterState> EnemyCurrentAIState;

	UPROPERTY()
	TArray<FCharacterState> EnemyOldAIState;
	
	TMap<FString, FCharacterState> completeList;

	
	AHeroBattleHero* m_owner;
	UAISimCharacter* m_SimOwner;

	FCharacterState m_ownerState;
	UAISimCharacter* character;
};
