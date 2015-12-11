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

	// value ist the incoming heal or damage
	// damage is always negative and heal always Positve
	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value);

	virtual bool isExpired();

	virtual void update(float deltaTime);

private:
	int usage;
	bool haveUsages;

	int blockChance;
	
	
};
