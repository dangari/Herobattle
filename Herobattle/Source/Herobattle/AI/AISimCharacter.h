// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/BaseCharacter.h"
#include "HBBlackboard.h"
#include "AISimCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API AAISimCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	void init(FCharacterState state);
	void init(FCharacterProperties character);

	void simulate(TArray<FSimAction> actionList, TMap<FString, FCharacterState> characterList, float DeltaTime);

	void simulateAction(FSimAction &action, TMap<FString, FCharacterState> &characterList, float duration);



private:

	void applyCondition(TArray<Condition> conditions);
	void applyDummyBuff();	

	void simulateAutoAttack();
	
	int getSlot(USkill* skill);


	FVector m_location;
	int m_attackers;
	int m_caster;

	bool m_isCasting = false;
	bool m_isAutoAttacking = false;
	bool m_isBuffed = false;
	bool m_isHexed = false;
	bool m_hasStance = false;
};
