// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "PerformAction.h"
#include "AIGameState.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Skills/Skill.h"




EBTNodeResult::Type UPerformAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}

AIAction UPerformAction::getNextAction(UBehaviorTreeComponent& OwnerComp)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	FName keyName = "AIGameState";
	UAIGameState* aiGameState = (UAIGameState*)BlackboardComp->GetValue<UBlackboardKeyType_Object>(keyName);
	if (aiGameState)
	{

	}
	return AIAction::IDLE;
}

void UPerformAction::calcSkillScore(UAIGameState* aiGameState)
{
	ABaseCharacter* owner = aiGameState->getOwner();
	for (int i = 0; i < 8; i++)
	{
		USkill* skill = owner->skillList[i];
		if (skill && !(owner->skillIsOnCooldown(i)))
		{
			FActionScore actionScore;
			if (skill->targetType == TargetType::ENEMY)
			{

			}
			else if (skill->targetType == TargetType::FRIEND)
			actionScore.score = skill->getScore(aiGameState);

			m_ActionList.Add(actionScore);
		}
	}
}
