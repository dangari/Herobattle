// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Buff/BaseBuffCompenent.h"
#include "BcAttackSpeed.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcAttackSpeed : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:
	UBcAttackSpeed();
	~UBcAttackSpeed();

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties);

	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0);

	virtual bool isExpired();

	virtual void update(float deltaTime);

	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration);
	
private:
	float m_AttackSpeed;
};
