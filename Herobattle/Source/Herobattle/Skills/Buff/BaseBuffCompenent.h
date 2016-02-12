// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Enum/SkillEnums.h"
#include "BuffContainer.h"
#include "XmlParser.h"
#include "AI/CharacterState.h"
#include "../Skill.h"
#include "BaseBuffCompenent.generated.h"

/**
 * 
 */

class ABaseCharacter;
class FXmlNode;
class USkillScore;
class UAISimCharacter;
class UBuff;

UCLASS()
class HEROBATTLE_API UBaseBuffCompenent : public UObject
{
	GENERATED_BODY()
	
public:

	UBaseBuffCompenent();
	~UBaseBuffCompenent();

	virtual void init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff);
	virtual void initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff);
	// value ist the incoming heal or damage
	// damage is always negative and heal always Positve
	virtual bool run(ABaseCharacter* caster, ABaseCharacter* self, int value = 0);
	virtual bool runSim(UAISimCharacter* caster, UAISimCharacter* self, int value = 0);


	virtual bool isExpired();

	virtual void update(float deltaTime);

	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration);
	virtual float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration);

	virtual FString ToString();
	

	ABaseCharacter* owner;
	UAISimCharacter* sim_owner;
protected:
	
	int usage;
	TargetType targetType;

	ABaseCharacter* getTarget(ABaseCharacter* caster, ABaseCharacter* self);
	UAISimCharacter* getTargetSim(UAISimCharacter* caster, UAISimCharacter* self);

	FSkillProperties m_properties;

};
