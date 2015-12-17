// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Buff/BaseBuffCompenent.h"
#include "BcBlock.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcBlock : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:

	UBcBlock();
	~UBcBlock();

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner);

	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0);

	virtual bool isExpired();

	virtual void update(float deltaTime);

	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration);

private:
	int usage;
	bool haveUsages;

	int blockChance;

	SkillType blockType;
	
	
};
