// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "BcGiveMana.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcGiveMana : public UBaseBuffCompenent
{
	GENERATED_BODY()

public:

	UBcGiveMana();
	~UBcGiveMana();
	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner) override;

	virtual bool isExpired() override;

	virtual FString ToString() override;
	
private:
	int treshhold = -10;
	int m_mana;
	
};
