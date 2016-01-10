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
}

UPerformAction::~UPerformAction()
{

}

EBTNodeResult::Type UPerformAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	switch (getNextAction(OwnerComp))
	{
	case AIAction::SKILL:
		m_owner->UseSkill(nextSkill.target, nextSkill.slot);
		m_owner->selectedTarget = nextSkill.target;
		break;
	case  AIAction::AUTOATACK:
		m_owner->setState(HBCharacterState::AUTOATTACK,nextSkill.target);
		break;
	default:
		break;
	}
	return EBTNodeResult::Succeeded;
}

AIAction UPerformAction::getNextAction(UBehaviorTreeComponent& OwnerComp)
{

	FActionScore attackScore;
	FActionScore skillScore;
	attackScore.score = 0.f;
	skillScore.score = 0.f;
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FName keyName = "AIGameState";
	UAIGameState* aiGameState = Cast<UAIGameState>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(keyName));
	

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
	else
	{
		attackScore.score = 0.2f;
		attackScore.action = AIAction::IDLE;
		m_ActionList.Add(attackScore);
	}

	if (m_ActionList.Num() > 0)
	{
		FActionScore action = getBestScore();
		if (action.action == AIAction::SKILL)
		nextSkill = action;
		m_ActionList.Empty();
		return action.action;

		
	}
	else
	{
		return AIAction::IDLE;
	}
	


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



void UPerformAction::TemporalSkillScore(UAIGameState* aiGameState, ABaseCharacter* owner)
{
	TArray<FActionScore> tempActionList;
	UAIGameState* newGameState = aiGameState;
	AAISimCharacter* character = NewObject<AAISimCharacter>();
	character->init(owner->getProperties());


	getSkillScore(newGameState, owner, 2);

	
	FActionScore action = getBestScore();
	tempActionList.Add(action);
	float DeltaTime = 0.5f;
	if (action.action == AIAction::AUTOATACK)
	{
		DeltaTime = owner->getWeapon().attackSpeed;
	}
	if (action.action == AIAction::SKILL)
	{
		DeltaTime = m_owner->skillList[action.slot]->properties.castTime;
	}
	newGameState->newState(character);
	newGameState = newGameState->simulate(DeltaTime);
	//character->simulate()
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

TArray<FActionScore> UPerformAction::getSkillScore(UAIGameState* newGameState, ABaseCharacter* owner, int depth)
{
	TArray<FActionScore> temporalActionScoreList;
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
		TArray<FActionScore> bestAction;
		bestAction.Add(temporalActionScoreList[0]);
		return bestAction;
		
	}
	else
	{
		simulateNextState(newGameState, temporalActionScoreList, depth);
	}
	

	return temporalActionScoreList;

}

void UPerformAction::simulateNextState(UAIGameState* newGameState, TArray<FActionScore> actionList, int depth)
{

	FActionScore attackScore = getBestAutoAttack(newGameState->getEnemyCurrentAIState());


	if (attackScore.score > 0)
	{
		attackScore.score = 0.2f;
		actionList.Add(attackScore);
	}
	else
	{
		attackScore.score = 0.2f;
		attackScore.action = AIAction::IDLE;
		actionList.Add(attackScore);
	}

	for (auto& action : actionList)
	{
		FSimAction simAction;
		simAction.action = action.action;
		simAction.ownerName = m_owner->m_Name;
		simAction.targetName = action.target->m_Name;
		switch (action.action)
		{
		case AIAction::IDLE:
			simAction.time = 0.5;
			break;
		case AIAction::AUTOATACK:
			simAction.time = m_owner->getWeapon().attackSpeed;
			break;
		case AIAction::SKILL:
			simAction.time = m_owner->skillList[action.slot]->properties.castTime;
			break;
		default:
			break;
		}
		AAISimCharacter* character = NewObject<AAISimCharacter>();
		character->init(m_owner->getProperties());
		AHerobattleCharacter* hbCharacter = Cast<AHerobattleCharacter>(m_owner->owningPlayer);
		TMap<FString, FCharacterState> charachterList = newGameState->getCharacterList();
		character->simulate(hbCharacter->blackboard->getTargetAction(m_owner->m_Name), charachterList, simAction.time);
		character->simulateAction(simAction, charachterList, 0.f);


		newGameState->newState(character);
		newGameState = newGameState->simulate(simAction.time);
		charachterList = newGameState->getCharacterList();
		AAISimCharacter* targetCharacter = NewObject<AAISimCharacter>();
		targetCharacter->init(*charachterList.Find(simAction.targetName));
		targetCharacter->simulateAction(simAction, charachterList, 0.f);
		newGameState->replaceState(targetCharacter->AiExtractor(character));

	}
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
