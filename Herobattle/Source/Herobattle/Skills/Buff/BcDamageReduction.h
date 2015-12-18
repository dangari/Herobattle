// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Buff/BaseBuffCompenent.h"
#include "BcDamageReduction.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcDamageReduction : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:

	UBcDamageReduction();
	~UBcDamageReduction();
	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration) override;

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner) override;

	virtual bool isExpired() override;

	virtual FString ToString() override;

private:
	int treshhold = -10;
	int m_Reduction;
	ReductionType m_RType;
	
	
};
