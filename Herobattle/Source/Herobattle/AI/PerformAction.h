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
	int slot = 0;
	float score;
	FString targetName;

	inline static bool ConstPredicate(const FActionScore ip1, const FActionScore ip2)
	{
		return (ip1.score > ip2.score);
	}
};

USTRUCT()
struct FTemporalActionScore
{

	GENERATED_USTRUCT_BODY()
	TArray<FActionScore> actionList;
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

	void DestroyObj(UObject* obj);

	FActionScore getNextAction(UAIGameState* aiGameState);
	void fillScoreList(UAIGameState* aiGameState);
	//calculates score for characterstate
	void calcSkillScore(TArray<FCharacterState> characterState, USkill* skill, int slot);
	// calculates score for character most time this function is used for the owner
	void calcSkillScore(FCharacterState characterState, USkill* skill, int slot);

	FActionScore TemporalSkillScore(UAIGameState* aiGameState, ABaseCharacter* owner);

	TArray<FActionScore> calcTempSkillScore(UAISimCharacter* owner, TArray<FCharacterState> characterState, USkill* skill, int slot);
	// calculates score for character most time this function is used for the owner
	TArray<FActionScore> calcTempSkillScore(UAISimCharacter* owner, FCharacterState characterState, USkill* skill, int slot);

	TArray<FActionScore> getSkillScore(UAIGameState* newGameState, UAISimCharacter* owner, int depth, float startTime);

	UAIGameState* simulateNextState(UAIGameState* newGameState,FActionScore action, float startTime);



	FActionScore getBestAutoAttack(TArray<FCharacterState> chracterState);

	FActionScore getBestScore();
	float getActionTime(FActionScore action);
	TArray<FActionScore> m_ActionList;


	AHeroBattleHero* m_owner;
	FActionScore nextSkill;
	bool temporalPlanning;

	UPROPERTY()
	UAISimCharacter* targetCharacter;
	UPROPERTY()
	UAISimCharacter* character;

	int count = 0;
	float m_attackScore = 0.2;
};
