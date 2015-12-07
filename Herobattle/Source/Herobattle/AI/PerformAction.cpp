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
	default:
		break;
	}
	return EBTNodeResult::Succeeded;
}

AIAction UPerformAction::getNextAction(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FName keyName = "AIGameState";
	UAIGameState* aiGameState = (UAIGameState*)BlackboardComp->GetValue<UBlackboardKeyType_Object>(keyName);
	if (aiGameState)
	{
		fillScoreList(aiGameState);
	}
	FActionScore score;
	if (m_ActionList.Num() > 0)
	{
		score = getBestScore();
		m_ActionList.Empty();
	}
	else
		return AIAction::IDLE;
	if (score.score > 0.1)
	{
		nextSkill = score;
		return AIAction::SKILL;
	}
	return AIAction::IDLE;
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
				switch (skill->targetType)
				{
				case TargetType::ENEMY:
					calcSkillScore(aiGameState->getEnemyCurrentAIState(), skill, i);
					break;
				case  TargetType::FRIEND:
					calcSkillScore(aiGameState->getAlliesCurrentAIState(), skill, i);
					break;
				case TargetType::SELFFREND:
					calcSkillScore(aiGameState->getAlliesCurrentAIState(), skill, i);
					calcSkillScore(m_owner, skill, i);
					break;
				case  TargetType::SELF:
					calcSkillScore(m_owner, skill, i);
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

void UPerformAction::calcSkillScore(ABaseCharacter* character, USkill* skill, int slot)
{
	FCharacterState characterState = character->AiExtractor(character);
	float score = skill->getScore(m_owner, characterState);
	if (score > 0)
	{
		FActionScore aScore;
		aScore.action = AIAction::SKILL;
		aScore.slot = slot;
		aScore.target = characterState.self;
		aScore.score = score;
	}
}

FActionScore UPerformAction::getBestScore()
{
	m_ActionList.Sort(FActionScore::ConstPredicate);
	return m_ActionList[0];
}
