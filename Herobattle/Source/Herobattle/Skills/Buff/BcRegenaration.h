// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Buff/BaseBuffCompenent.h"
#include "BcRegenaration.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcRegenaration : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:

	UBcRegenaration();
	~UBcRegenaration();

	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0) override;
	virtual bool runSim(UAISimCharacter* caster, UAISimCharacter* self, int value = 0) override;

	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration) override;
	virtual float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration) override;

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff) override;
	virtual void initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff) override;

	virtual bool isExpired() override;

	virtual FString ToString() override;
	
private:
	int m_Regenration;
	RegnerationType type;
	
	
};
