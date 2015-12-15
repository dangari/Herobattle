// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Buff/BaseBuffCompenent.h"
#include "BcReduceMana.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcReduceMana : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:
	UBcReduceMana();
	~UBcReduceMana();

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner);

	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0);

	virtual bool isExpired();

	virtual void update(float deltaTime);
	
private:
	int usage;
	bool haveUsages;
	
	int reduction;
};
