// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "PerformAction.h"
#include "AIGameState.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Skills/Skill.h"
#include "AISimCharacter.h"
#include "HerobattleCharacter.h"




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
	FActionScore action;

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FName keyName = "AIGameState";
	UAIGameState* aiGameState = Cast<UAIGameState>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(keyName));

	if (aiGameState)
	{
		if (temporalPlanning)
		{
			action = TemporalSkillScore(aiGameState, m_owner);
		}
		else
		{
			action = getNextAction(aiGameState);
		}
		switch (action.action)
		{
		case AIAction::SKILL:
			m_owner->UseSkill(action.target, action.slot);
			m_owner->selectedTarget = action.target;
			break;
		case  AIAction::AUTOATACK:
			m_owner->setState(HBCharacterState::AUTOATTACK, action.target);
			break;
		default:
			break;
		}
	}
	return EBTNodeResult::Succeeded;
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
		float score = skill->getScore(m_owner, character);
		if (score > 0)
		{
			FActionScore aScore;
			aScore.action = AIAction::SKILL;
			aScore.slot = slot;
			aScore.target = character.self;
			aScore.score = score;
			m_ActionList.Add(aScore);
		}
	}
}

void UPerformAction::calcSkillScore(FCharacterState characterState, USkill* skill, int slot)
{
	float score = skill->getScore(m_owner, characterState);
	if (score > 0)
	{
		FActionScore aScore;
		aScore.action = AIAction::SKILL;
		aScore.slot = slot;
		aScore.target = characterState.self;
		aScore.score = score;
		m_ActionList.Add(aScore);
	}
}





TArray<FActionScore> UPerformAction::calcTempSkillScore(ABaseCharacter* owner, TArray<FCharacterState> characterState, USkill* skill, int slot)
{
	TArray<FActionScore> actionList;

	for (auto& character : characterState)
	{
		float score = skill->getScore(owner, character);
		if (score > 0)
		{
			FActionScore aScore;
			aScore.action = AIAction::SKILL;
			aScore.slot = slot;
			aScore.target = character.self;
			aScore.score = score;
			actionList.Add(aScore);
		}
	}
	return actionList;
}

TArray<FActionScore> UPerformAction::calcTempSkillScore(ABaseCharacter* owner, FCharacterState characterState, USkill* skill, int slot)
{
	TArray<FActionScore> actionList;
	float score = skill->getScore(owner, characterState);
	if (score > 0)
	{
		FActionScore aScore;
		aScore.action = AIAction::SKILL;
		aScore.slot = slot;
		aScore.target = characterState.self;
		aScore.score = score;
		actionList.Add(aScore);
	}

	return actionList;
}

FActionScore UPerformAction::TemporalSkillScore(UAIGameState* aiGameState, ABaseCharacter* owner)
{
	if (owner && aiGameState->getOwner())
	{
		TArray<FActionScore> tempActionList;
		UAIGameState* newGameState = aiGameState;
		AHerobattleCharacter* character = Cast<AHerobattleCharacter>(m_owner->owningPlayer);
	
		TArray<FActionScore> bestActionList = getSkillScore(newGameState, owner, 1);
		TArray<USimAction*> simActionList;
		int size = bestActionList.Num() - 1;
		float time = 0.f;
		for (int i = size; i >= 0; i--)
		{
			FActionScore action = bestActionList[i];
			USimAction* simAction = NewObject<USimAction>();
			simAction->action = action.action;
			simAction->targetName = action.target->m_Name;
			simAction->ownerName = owner->m_Name;
			simAction->skill = owner->skillList[action.slot];
			switch (action.action)
			{
			case AIAction::IDLE:
				time += 0.5;
				break;
			case AIAction::AUTOATACK:
				time += owner->getWeapon().attackSpeed;
				break;
			case AIAction::SKILL:
				time += simAction->skill->properties.castTime;
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

TArray<FActionScore> UPerformAction::getSkillScore(UAIGameState* newGameState, ABaseCharacter* owner, int depth)
{
	
	TArray<FActionScore> temporalActionScoreList;

	FActionScore attackScore = getBestAutoAttack(newGameState->getEnemyCurrentAIState());
	if (attackScore.score > 0)
	{
		attackScore.score = 0.2f;
		temporalActionScoreList.Add(attackScore);
	}
	else
	{
		attackScore.score = 0.2f;
		attackScore.action = AIAction::IDLE;
		attackScore.target = m_owner;
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
		bestActionList.Add(temporalActionScoreList[0]);
		return bestActionList;
		
	}
	else
	{
		FActionScore bestAction;
		bestAction.score = 0.f;
		TArray<FActionScore> bestActionList;
		int newDepth = depth--;
		for (auto& action : temporalActionScoreList)
		{
			UAIGameState* nextGameState = simulateNextState(newGameState, action);
			TArray<FActionScore> bestTempActionList = getSkillScore(nextGameState, nextGameState->getOwner(), newDepth);
			float score = 0.f;
			for (auto& tempAction : bestTempActionList)
			{
				score = action.score * tempAction.score;
				if (score < bestAction.score)
				{
					bestAction = tempAction;
					bestActionList = bestTempActionList;
				}
			}
		}
		bestActionList.Add(bestAction);
		return bestActionList;
		
	}
	

	return temporalActionScoreList;

}

UAIGameState* UPerformAction::simulateNextState(UAIGameState* newGameState,FActionScore action)
{

	USimAction* simAction = NewObject<USimAction>();
	simAction->action = action.action;
	simAction->ownerName = m_owner->m_Name;
	simAction->targetName = action.target->m_Name;
	switch (action.action)
	{
	case AIAction::IDLE:
		simAction->time = 0.5;
		break;
	case AIAction::AUTOATACK:
		simAction->time = m_owner->getWeapon().attackSpeed;
		break;
	case AIAction::SKILL:
		simAction->time = m_owner->skillList[action.slot]->properties.castTime;
		simAction->skill = m_owner->skillList[action.slot];
		break;
	default:
		break;
	}
	UAISimCharacter* character = NewObject<UAISimCharacter>();
	character->init(m_owner->getProperties());
	AHerobattleCharacter* hbCharacter = Cast<AHerobattleCharacter>(m_owner->owningPlayer);
	TMap<FString, FCharacterState> charachterList = newGameState->getCharacterList();
	character->simulate(hbCharacter->getBlackBoard()->getTargetAction(m_owner->m_Name), charachterList, simAction->time);
	character->simulateAction(simAction, charachterList, 0.f);


	newGameState = newGameState->simulate(simAction->time);
	charachterList = newGameState->getCharacterList();
	UAISimCharacter* targetCharacter = NewObject<UAISimCharacter>();
	targetCharacter->init(*charachterList.Find(simAction->targetName));
	targetCharacter->simulateAction(simAction, charachterList, 0.f);
	newGameState->replaceState(targetCharacter->AiExtractor(character));
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
		aScore.target = state.self;
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
