// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "Enum/AIEnums.h"
#include "CharacterState.h"
#include "PerformAction.generated.h"

class ABaseCharacter;
class UAIGameState;

USTRUCT()
struct FActionScore
{

	GENERATED_USTRUCT_BODY()
	AIAction action;
	int slot;
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
	UPerformAction();
	~UPerformAction();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	

	

private:
	AIAction getNextAction(UBehaviorTreeComponent& OwnerComp);
	void fillScoreList(UAIGameState* aiGameState);
	//calculates score for characterstate
	void calcSkillScore(TArray<FCharacterState> chracterState, USkill* skill, int slot);
	// calculates score for character most time this function is used for the owner
	void calcSkillScore(FCharacterState characterState, USkill* skill, int slot);

	void TemporalSkillScore(UAIGameState* aiGameState);

	FActionScore getBestAutoAttack(TArray<FCharacterState> chracterState);

	FActionScore getBestScore();
	TArray<FActionScore> m_ActionList;
	AHeroBattleHero* m_owner;
	FActionScore nextSkill;
};
