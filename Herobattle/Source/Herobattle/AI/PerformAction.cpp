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

void UPerformAction::fillScoreList(UAIGameState& aiGameState)
{
	ABaseCharacter* owner = aiGameState.getOwner();
	for (int i = 0; i < 8; i++)
	{
		USkill* skill = owner->skillList[i];
		if (skill && !(owner->skillIsOnCooldown(i)))
		{
			switch (skill->targetType)
			{
			case TargetType::ENEMY:
				calcSkillScore(aiGameState.getEnemyCurrentAIState(), skill, i);
				break;
			case  TargetType::FRIEND:
				calcSkillScore(aiGameState.getAlliesCurrentAIState(), skill, i);
				break;
			case TargetType::SELFFREND:
				calcSkillScore(aiGameState.getAlliesCurrentAIState(), skill, i);
				calcSkillScore(owner, skill, i);
				break;
			case  TargetType::SELF:
				calcSkillScore(owner, skill, i);
				break;
			default:
				break;
			}
		}
	}
}

void UPerformAction::calcSkillScore(TArray<FCharacterState> characterState, USkill* skill, int slot)
{
	for (FCharacterState& character : characterState)
	{
		float score = skill->getScore(character);
		if (score > 0)
		{
			FActionScore aScore;
			aScore.action = AIAction::SKILL;
			aScore.slot = slot;
			aScore.target = character.self;
			aScore.score = score;
		}
	}
}

void UPerformAction::calcSkillScore(ABaseCharacter* character, USkill* skill, int slot)
{
	FCharacterState characterState = character->AiExtractor(character);
	float score = skill->getScore(characterState);
	if (score > 0)
	{
		FActionScore aScore;
		aScore.action = AIAction::SKILL;
		aScore.slot = slot;
		aScore.target = characterState.self;
		aScore.score = score;
	}
}
