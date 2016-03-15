// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "PerformAction.h"
#include "AIGameState.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Skills/Skill.h"
#include "AISimCharacter.h"
#include "HerobattleCharacter.h"
#include "HerobattleHero.h"




UPerformAction::UPerformAction()
{
	bCreateNodeInstance = true;
	temporalPlanning = true;
}

UPerformAction::~UPerformAction()
{

}

EBTNodeResult::Type UPerformAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	count++;
	FActionScore action;

	if (!character)
		character = NewObject<UAISimCharacter>(this);
	if (!targetCharacter)
		targetCharacter = NewObject<UAISimCharacter>(this);

	

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FName keyName = "AIGameState";
	UAIGameState* aiGameState = Cast<UAIGameState>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(keyName));

	

	if (aiGameState && aiGameState->m_owner && aiGameState->m_owner->m_State != HBCharacterState::DEATH)
	{
		aiGameState->UpdateAttackerNumber();
		TMap<FString, ABaseCharacter*> characterList = aiGameState->getCharacterInstanceList();
		if (temporalPlanning)
		{
			action = TemporalSkillScore(aiGameState, m_owner);
		}
		else
		{
			action = getNextAction(aiGameState);
		}
		ABaseCharacter* target = nullptr;
		if (characterList.Contains(action.targetName))
		{
			target = *characterList.Find(action.targetName);
			switch (action.action)
			{
			case AIAction::SKILL:
				m_owner->UseSkill(target, action.slot);
				m_owner->selectedTarget = target;
				break;
			case  AIAction::AUTOATACK:
				m_owner->setState(HBCharacterState::AUTOATTACK, target);
				m_owner->selectedTarget = target;
				break;
			default:
				break;
			}
		}
		
		
	}

	return EBTNodeResult::Succeeded;
}

void UPerformAction::DestroyObj(UObject* obj)
{
	if (!obj) return;
	if (!obj->IsValidLowLevel()) return;

	obj->ConditionalBeginDestroy(); //instantly clears UObject out of memory
	obj = nullptr;
}

FActionScore UPerformAction::getNextAction(UAIGameState* aiGameState)
{

	FActionScore attackScore;
	FActionScore skillScore;
	attackScore.score = 0.f;
	skillScore.score = 0.f;
	
	

	if (aiGameState && aiGameState->getOwner())
	{
		fillScoreList(aiGameState);
		attackScore = getBestAutoAttack(aiGameState->getEnemyCurrentAIState());
	}

	if (attackScore.score > 0)
	{
		attackScore.score = 0.2f;
		m_ActionList.Add(attackScore);
	}

	FActionScore idleScore;
	idleScore.score = 0.19f;
	idleScore.action = AIAction::IDLE;
	m_ActionList.Add(idleScore);



	FActionScore action = getBestScore();
	if (action.action == AIAction::SKILL)
		nextSkill = action;
	m_ActionList.Empty();
	return action;

	


}

void UPerformAction::fillScoreList(UAIGameState* aiGameState)
{
	
	if (m_owner)
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_owner->canUseSkill(i))
			{
				USkill* skill = m_owner->skillList[i];
				if (skill && !(m_owner->skillIsOnCooldown(i)))
				{
					switch (skill->properties.targetType)
					{
					case TargetType::ENEMY:
						calcSkillScore(aiGameState->getEnemyCurrentAIState(), skill, i);
						break;
					case  TargetType::FRIEND:
						calcSkillScore(aiGameState->getAlliesCurrentAIState(), skill, i);
						break;
					case TargetType::SELFFRIEND:
						calcSkillScore(aiGameState->getAlliesCurrentAIState(), skill, i);
						calcSkillScore(aiGameState->getOwnerState(), skill, i);
						break;
					case  TargetType::SELF:
						calcSkillScore(aiGameState->getOwnerState(), skill, i);
						break;
					default:
						break;
					}
				}
			}
		}
	}
	else
		m_owner = aiGameState->getOwner();
}

void UPerformAction::calcSkillScore(TArray<FCharacterState> characterState, USkill* skill, int slot)
{
	for (FCharacterState& character : characterState)
	{
		if (skill->properties.range > character.airDistance)
		{
			float score = skill->getScore(m_owner, character);
			if (score > 0)
			{
				FActionScore aScore;
				aScore.action = AIAction::SKILL;
				aScore.slot = slot;
				aScore.targetName = character.name;
				aScore.score = score;
				m_ActionList.Add(aScore);
			}
		}
	}
}

void UPerformAction::calcSkillScore(FCharacterState characterState, USkill* skill, int slot)
{
	if (skill->properties.range > characterState.airDistance)
	{
		float score = skill->getScore(m_owner, characterState);
		if (score > 0)
		{
			FActionScore aScore;
			aScore.action = AIAction::SKILL;
			aScore.slot = slot;
			aScore.targetName = characterState.name;
			aScore.score = score;
			m_ActionList.Add(aScore);
		}
	}
}





TArray<FActionScore> UPerformAction::calcTempSkillScore(UAISimCharacter* owner, TArray<FCharacterState> characterState, USkill* skill, int slot)
{
	TArray<FActionScore> actionList;

	for (auto& character : characterState)
	{
		if (skill->properties.range > character.airDistance)
		{
			float score = skill->getScoreSim(owner, character);
			if (score > 0)
			{
				FActionScore aScore;
				aScore.action = AIAction::SKILL;
				aScore.slot = slot;
				aScore.targetName = character.name;
				aScore.score = score;
				actionList.Add(aScore);
			}
		}
	}
	return actionList;
}

TArray<FActionScore> UPerformAction::calcTempSkillScore(UAISimCharacter* owner, FCharacterState characterState, USkill* skill, int slot)
{
	TArray<FActionScore> actionList;
	float score = skill->getScoreSim(owner, characterState);
	if (skill->properties.range > characterState.airDistance)
	{
	if (score > 0)
		{
			FActionScore aScore;
			aScore.action = AIAction::SKILL;
			aScore.slot = slot;
			aScore.targetName = characterState.name;
			aScore.score = score;
			actionList.Add(aScore);
		}
	}

	return actionList;
}

FActionScore UPerformAction::TemporalSkillScore(UAIGameState* aiGameState, ABaseCharacter* owner)
{
	if (owner && aiGameState->getOwner())
	{
		TArray<FActionScore> tempActionList;
		UAIGameState* newGameState = aiGameState->copy();
		character->init(m_owner->getProperties());
		newGameState->setSimOwner(character);
		AHerobattleCharacter* character = Cast<AHerobattleCharacter>(m_owner->owningPlayer);
	
		UAISimCharacter* simOwner = NewObject<UAISimCharacter>(this);
		simOwner->init(owner->getProperties());
		newGameState->UpdateAttackerNumber();
		TArray<FActionScore> bestActionList = getSkillScore(newGameState, simOwner, 1, 0);
		TArray<USimAction*> simActionList;
		int size = bestActionList.Num() - 1;
		float time = 0.f;
		for (int i = size; i >= 0; i--)
		{
			FActionScore action = bestActionList[i];
			USimAction* simAction = NewObject<USimAction>();
			simAction->action = action.action;
			simAction->ownerName = owner->m_Name;
			simAction->skill = owner->skillList[action.slot];
			switch (action.action)
			{
			case AIAction::IDLE:
				time += 0.5;
				break;
			case AIAction::AUTOATACK:
				time += owner->getWeapon().attackSpeed;
				simAction->targetName = action.targetName;
				break;
			case AIAction::SKILL:
				time += simAction->skill->properties.castTime;
				simAction->targetName = action.targetName;
				break;
			default:
				break;
			}
			simActionList.Add(simAction);
			
		}
		character->getBlackBoard()->addAction(m_owner->m_Name, simActionList);
		return bestActionList[bestActionList.Num() - 1];
	}
	else
	{
		m_owner = aiGameState->getOwner();
	}
		
	FActionScore action;
	action.action = AIAction::IDLE;
	
	return action;
}

TArray<FActionScore> UPerformAction::getSkillScore(UAIGameState* newGameState, UAISimCharacter* owner, int depth, float StartTime)
{
	
	TArray<FActionScore> temporalActionScoreList;

	FActionScore attackScore = getBestAutoAttack(newGameState->getEnemyCurrentAIState());
	if (attackScore.score > 0)
	{
		attackScore.score = m_attackScore;
		temporalActionScoreList.Add(attackScore);
	}
	else
	{
		attackScore.score = 0.2f;
		attackScore.action = AIAction::IDLE;
		attackScore.targetName = m_owner->m_Name;
		temporalActionScoreList.Add(attackScore);
	}

	for (int i = 0; i < 8; i++)
	{
		if (owner->canUseSkill(i))
		{
			USkill* skill = owner->skillList[i];
			if (skill && !(owner->skillIsOnCooldown(i)))
			{
				switch (skill->properties.targetType)
				{
				case TargetType::ENEMY:
					temporalActionScoreList.Append(calcTempSkillScore(owner, newGameState->getEnemyCurrentAIState(), skill, i));
					break;
				case  TargetType::FRIEND:
					temporalActionScoreList.Append(calcTempSkillScore(owner, newGameState->getAlliesCurrentAIState(), skill, i));
					break;
				case TargetType::SELFFRIEND:
					temporalActionScoreList.Append(calcTempSkillScore(owner, newGameState->getAlliesCurrentAIState(), skill, i));
					temporalActionScoreList.Append(calcTempSkillScore(owner, newGameState->getOwnerState(), skill, i));
					break;
				case  TargetType::SELF:
					temporalActionScoreList.Append(calcTempSkillScore(owner, newGameState->getOwnerState(), skill, i));
					break;
				default:
					break;
				}
			}
		}
	}
	if (depth == 0)
	{
		temporalActionScoreList.Sort(FActionScore::ConstPredicate);
		TArray<FActionScore> bestActionList;
		FActionScore bestAction = temporalActionScoreList[0];
		bestActionList.Add(bestAction);
		return bestActionList;
		
	}
	else
	{
		FActionScore bestAction;
		bestAction.score;
		float bestScore = 0.f;
		TArray<FActionScore> bestActionList;
		for (auto& action : temporalActionScoreList)
		{
			float time = StartTime + getActionTime(action);
			UAIGameState* nextGameState = simulateNextState(newGameState, action, StartTime);
			TArray<FActionScore> bestTempActionList = getSkillScore(nextGameState, nextGameState->getSimOwner(), depth - 1, time);
			float score = action.score;
			for (auto& tempAction : bestTempActionList)
			{
				score = score * tempAction.score;
				
			}
			if (score > bestScore)
			{
				bestAction = action;
				bestActionList = bestTempActionList;
			}
			DestroyObj(nextGameState);

		}
		bestActionList.Add(bestAction);
		return bestActionList;
		
	}
	

	return temporalActionScoreList;

}

UAIGameState* UPerformAction::simulateNextState(UAIGameState* newGameState,FActionScore action, float startTime)
{

	USimAction* simAction = NewObject<USimAction>();
	simAction->action = action.action;
	simAction->ownerName = m_owner->m_Name;
	simAction->targetName = action.targetName;
	simAction->time = getActionTime(action);
	if (action.action == AIAction::SKILL)
	{
		simAction->skill = m_owner->skillList[action.slot];
	}
	UAISimCharacter* newOwner = NewObject<UAISimCharacter>(m_owner);
	newOwner->init(newGameState->getSimOwner()->getProperties());
	AHerobattleCharacter* hbCharacter = Cast<AHerobattleCharacter>(m_owner->owningPlayer);
	TMap<FString, FCharacterState> charachterList = newGameState->getCharacterList();
	newOwner->simulate(hbCharacter->getBlackBoard()->getTargetAction(m_owner->m_Name, startTime, simAction->time), charachterList, simAction->time);
	newOwner->simulateAction(simAction, charachterList, 0.f);


	newGameState = newGameState->simulate(simAction->time, startTime, simAction->time);
	charachterList = newGameState->getCharacterList();
	
	if (simAction->targetName.Equals(newOwner->m_Name))
	{
		newGameState->setSimOwner(character);
	}
	else
	{
		targetCharacter->init(*charachterList.Find(simAction->targetName));
		targetCharacter->simulateAction(simAction, charachterList, 0.f, false);
		newGameState->replaceState(targetCharacter->AiExtractor(character));
		newGameState->setSimOwner(newOwner);
	}
	
	
	DestroyObj(simAction);
	newGameState->UpdateAttackerNumber();
	return newGameState;
}

FActionScore UPerformAction::getBestAutoAttack(TArray<FCharacterState> chracterState)
{
	TArray<FActionScore> targetList;
	for (auto& state : chracterState)
	{
		float score = 0.f;
		score = 1 - (state.airDistance / state.weapon.range);
		FActionScore aScore;
		aScore.action = AIAction::AUTOATACK;
		aScore.targetName = state.name;
		aScore.score = score;
		targetList.Add(aScore);
	}
	targetList.Sort(FActionScore::ConstPredicate);
	if (targetList.Num() > 0)
		return targetList[0];
	else
	{
		FActionScore aScore;
		aScore.action = AIAction::AUTOATACK;
		aScore.score = 0.f;
		return aScore;
	}
}

FActionScore UPerformAction::getBestScore()
{
	m_ActionList.Sort(FActionScore::ConstPredicate);
	FActionScore first = m_ActionList[0];
	FActionScore last = m_ActionList[m_ActionList.Num() - 1];
	return m_ActionList[0];
}

float UPerformAction::getActionTime(FActionScore action)
{
	float time = 0.0f;
	switch (action.action)
	{
	case AIAction::IDLE:
		time = 0.5;
		break;
	case AIAction::AUTOATACK:
		time = m_owner->getWeapon().attackSpeed;
		break;
	case AIAction::SKILL:
		time = m_owner->skillList[action.slot]->properties.castTime;
		break;
	default:
		break;
	}
	return time;
}

