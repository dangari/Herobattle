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
	m_owner = Cast<AHeroBattleHero>(owner);
	m_ownerState = m_owner->AiExtractor(owner);
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
			if (enemy.selectedTarget == ally.self)
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
	if (m_owner->ETeam == state.ETeam)
	{
		for (auto& currentState : AlliesCurrentAIState)
		{
			if (state.name.Equals(currentState.name))
			{
				AlliesCurrentAIState.Remove(currentState);
				
			}
		}
		AlliesCurrentAIState.Add(state);
	}
	else
	{
		for (auto& currentState : EnemyCurrentAIState)
		{
			if (state.name.Equals(currentState.name))
			{
				EnemyCurrentAIState.Remove(currentState);
				
			}
		}
		EnemyCurrentAIState.Add(state);
	}
}

FCharacterState UAIGameState::getOwnerState()
{
	return m_ownerState;
}

UAIGameState* UAIGameState::simulate(float DeltaTime)
{
	UAIGameState* gameState = NewObject<UAIGameState>();
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

void UAIGameState::addDeltaTime(float DeltaTime)
{
	m_deltaTime += DeltaTime;
}

AHeroBattleHero* UAIGameState::getOwner()
{
	return m_owner;
}

void UAIGameState::simulateCharacter(float DeltaTime, TArray<FCharacterState> stateList, UAIGameState* gameState)
{
	AAISimCharacter* character = NewObject<AAISimCharacter>();
	TArray<FCharacterState> newStateList;
	for (auto& state : stateList)
	{
		AHerobattleCharacter* dummyCharacter = Cast<AHerobattleCharacter>(m_owner->owningPlayer);
		TArray<FSimAction> actionList = dummyCharacter->blackboard->getActions(state.name, DeltaTime);

		character->init(state);
		character->simulate(actionList, getCharacterList(), DeltaTime);
		gameState->addCharacterState(character->AiExtractor(m_owner));
	}
}

