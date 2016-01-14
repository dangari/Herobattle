// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Buff/BaseBuffCompenent.h"
#include "BcMovementSpeed.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcMovementSpeed : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:

	UBcMovementSpeed();
	~UBcMovementSpeed();

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff);
	virtual void initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff) override;


	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0);
	virtual bool runSim(UAISimCharacter* caster, UAISimCharacter* self, int value = 0) override;

	virtual bool isExpired();

	virtual void update(float deltaTime);

	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration);
	virtual float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration) override;

private:
	float m_MovementSpeed;
	
	
};
