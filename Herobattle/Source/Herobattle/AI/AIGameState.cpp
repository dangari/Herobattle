// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "AIGameState.h"
#include "Base/BaseCharacter.h"
#include "HeroBattleHero.h"
#include "Enum/CharacterEnums.h"
#include "HerobattleCharacter.h"
#include "HBBlackboard.h"
#include "AISimCharacter.h"




UAIGameState::UAIGameState()
{
	
}

UAIGameState::~UAIGameState()
{

}

void UAIGameState::newState(ABaseCharacter* owner)
{
	createSimCharacters();
	m_owner = Cast<AHeroBattleHero>(owner);
	m_ownerState = m_owner->AiExtractor(owner);
	m_SimOwner->init(owner->getProperties());

	EnemyOldAIState = EnemyCurrentAIState;
	TArray<FCharacterState> newEnemyState;
	EnemyCurrentAIState = newEnemyState;
	
	EnemyOldAIState = AlliesCurrentAIState;
	TArray<FCharacterState> newAlliesState;
	AlliesCurrentAIState = newEnemyState;

	m_deltaTime = 0.0f;
}

void UAIGameState::newStateSim(UAISimCharacter* owner)
{
	createSimCharacters();
	m_SimOwner = owner;
	m_ownerState = m_SimOwner->AiExtractor(m_SimOwner);
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






void UAIGameState::UpdateAttackerNumber()
{
	for (auto& ally : AlliesCurrentAIState)
	{
		for (auto enemy : EnemyCurrentAIState)
		{
			if (enemy.name.Equals(ally.name))
			{
				if (enemy.state == HBCharacterState::AUTOATTACK ||
					(enemy.state == HBCharacterState::CASTING && (enemy.skillType == SkillType::MELEEATTACK || enemy.skillType == SkillType::RANGEATTACK)))
				{
					ally.attackers++;
				}
				else if (enemy.state == HBCharacterState::CASTING)
				{
					ally.caster++;
				}

			}
		}
	}
	for (auto enemy : EnemyCurrentAIState)
	{
		if (enemy.selectedTarget == m_owner)
		{
			if (enemy.state == HBCharacterState::AUTOATTACK ||
				(enemy.state == HBCharacterState::CASTING && (enemy.skillType == SkillType::MELEEATTACK || enemy.skillType == SkillType::RANGEATTACK)))
			{
				m_ownerState.attackers++;
			}
			else if (enemy.state == HBCharacterState::CASTING)
			{
				m_ownerState.caster++;
			}

		}
	}

}

void UAIGameState::replaceState(FCharacterState state)
{

	TArray<FCharacterState> newStateList;
	if (m_owner->ETeam == state.ETeam)
	{
		for (auto& currentState : AlliesCurrentAIState)
		{
			if (!state.name.Equals(currentState.name))
			{
				newStateList.Add(currentState);
			}
		}
		newStateList.Add(state);
		AlliesCurrentAIState = newStateList;
	}
	else
	{
		for (auto& currentState : EnemyCurrentAIState)
		{
			if (!state.name.Equals(currentState.name))
			{
				newStateList.Add(currentState);
				
			}
		}
		newStateList.Add(state);
		EnemyCurrentAIState = newStateList;
	}
}

void UAIGameState::createSimCharacters()
{
	if (!m_SimOwner)
		m_SimOwner = NewObject<UAISimCharacter>(this);
	if (!character)
		character = NewObject<UAISimCharacter>(this);
}	

FCharacterState UAIGameState::getOwnerState()
{
	return m_ownerState;
}

UAIGameState* UAIGameState::simulate(float DeltaTime)
{
	UAIGameState* gameState = copy();
	gameState->newState(m_owner);
	simulateCharacter(DeltaTime, AlliesCurrentAIState, gameState);
	simulateCharacter(DeltaTime, EnemyCurrentAIState, gameState);
	return gameState;
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

TMap<FString, FCharacterState> UAIGameState::getCharacterList()
{
	TMap<FString, FCharacterState> completeList;
	for (auto& state : AlliesCurrentAIState)
	{
		FString name = state.name;
		completeList.Add(name, state);
	}
	for (auto& state : EnemyCurrentAIState)
	{
		FString name = state.name;
		completeList.Add(name, state);
	}
	FString name = m_ownerState.name;
	completeList.Add(name, m_ownerState);

	return completeList;
}

TMap<FString, ABaseCharacter*> UAIGameState::getCharacterInstanceList()
{
	TMap<FString, ABaseCharacter*> characterList;
	characterList.Add(m_owner->m_Name, m_owner);
	for (auto& state : AlliesCurrentAIState)
	{
		FString name = state.name;
		characterList.Add(name, state.self);
	}
	for (auto& state : EnemyCurrentAIState)
	{
		FString name = state.name;
		characterList.Add(name, state.self);
	}

	return characterList;
}

void UAIGameState::addDeltaTime(float DeltaTime)
{
	m_deltaTime += DeltaTime;
}

AHeroBattleHero* UAIGameState::getOwner()
{
	return m_owner;
}

UAIGameState* UAIGameState::copy()
{
	UAIGameState*  newGamestate = NewObject<UAIGameState>(this);
	newGamestate->AlliesCurrentAIState = AlliesCurrentAIState;
	newGamestate->EnemyCurrentAIState = EnemyCurrentAIState;
	newGamestate->AlliesOldAIState = AlliesOldAIState;
	newGamestate->EnemyOldAIState = EnemyOldAIState;
	newGamestate->m_owner = m_owner;
	newGamestate->m_ownerState = m_ownerState;

	newGamestate->m_SimOwner = m_SimOwner;
	return newGamestate;
}

void UAIGameState::simulateCharacter(float DeltaTime, TArray<FCharacterState> stateList, UAIGameState* gameState)
{
	AHerobattleCharacter* dummyCharacter = Cast<AHerobattleCharacter>(m_owner->owningPlayer);

	

	
	TArray<FCharacterState> newStateList;
	for (auto& state : stateList)
	{
		
		TArray<USimAction*> actionList = dummyCharacter->getBlackBoard()->getTargetAction(state.name);

		character->init(state);
		character->simulate(actionList, getCharacterList(), DeltaTime);
		gameState->addCharacterState(character->AiExtractor(m_SimOwner));
	}
}

void UAIGameState::setSimOwner(UAISimCharacter* character)
{
	m_SimOwner = character;
	m_ownerState = character->AiExtractor(character);
}

UAISimCharacter* UAIGameState::getSimOwner()
{
	return m_SimOwner;
}


