// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "Enum/AIEnums.h"
#include "CharacterState.h"
#include "PerformAction.generated.h"



USTRUCT()
struct FActionScore
{

	GENERATED_USTRUCT_BODY()
	AIAction action;
	float score;
	ABaseCharacter* target;

	inline static bool ConstPredicate(const FActionScore ip1, const FActionScore ip2)
	{
		return (ip1.score > ip2.score);
	}
};

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UPerformAction : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	

	

private:
	AIAction getNextAction(UBehaviorTreeComponent& OwnerComp);
	void fillScoreList(UAIGameState* aiGameState);
	void calcSkillScore(TArray<FCharacterState> chracterState, USkill* skill);
	TArray<FActionScore> m_ActionList;
};
