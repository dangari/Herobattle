// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseBuffCompenent.h"
#include "XmlParser.h"
#include "Base/BaseCharacter.h"
#include "AI/CharacterState.h"
#include "AI/SkillScore.h"
#include "Buff.h"
#include "AI/AISimCharacter.h"






UBaseBuffCompenent::UBaseBuffCompenent()
{

}

UBaseBuffCompenent::~UBaseBuffCompenent()
{

}

void UBaseBuffCompenent::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	m_properties = properties;
	this->owner = owner;
}

void UBaseBuffCompenent::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	m_properties = properties;
	sim_owner = owner;
}

bool UBaseBuffCompenent::isExpired()
{
	return false;
}

void UBaseBuffCompenent::update(float deltaTime)
{

}

float UBaseBuffCompenent::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 1.f;
}

float UBaseBuffCompenent::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 1.f;
}

FString UBaseBuffCompenent::ToString()
{
	return TEXT("");
}

ABaseCharacter* UBaseBuffCompenent::getTarget(ABaseCharacter* caster, ABaseCharacter* self)
{
	if (targetType == TargetType::SELF)
		return self;
	else if (targetType == TargetType::OWNER)
		return owner;
	else
		return caster;
}

UAISimCharacter* UBaseBuffCompenent::getTargetSim(UAISimCharacter* caster, UAISimCharacter* self)
{
	if (targetType == TargetType::SELF)
		return self;
	else if (targetType == TargetType::OWNER)
		return sim_owner;
	else
		return caster;
}

bool UBaseBuffCompenent::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	return true;
}

bool UBaseBuffCompenent::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	return true;
}
