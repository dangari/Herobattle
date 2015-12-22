// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "PerformAction.h"
#include "AIGameState.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Skills/Skill.h"




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


	if (m_ActionList.Num() > 0)
	{
		skillScore = getBestScore();
		m_ActionList.Empty();
	}
	if (skillScore.score > 0.2)
	{
		nextSkill = skillScore;
		return AIAction::SKILL;
	}
	else if (attackScore.score > 0)
	{
		nextSkill = attackScore;
		return AIAction::AUTOATACK;
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
		//aScore.slot = 0;
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
