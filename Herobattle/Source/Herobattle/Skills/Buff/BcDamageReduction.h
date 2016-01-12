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
	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties) override;
	virtual void initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties) override;

	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0) override;
	virtual bool runSim(UAISimCharacter* caster, UAISimCharacter* self, int value = 0) override;



	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration) override;
	virtual float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration) override;

	virtual bool isExpired() override;

	virtual FString ToString() override;

private:
	int treshhold = -10;
	int m_Reduction;
	ReductionType m_RType;
	
	
};
