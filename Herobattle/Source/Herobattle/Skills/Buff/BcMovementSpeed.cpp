// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcMovementSpeed.h"




UBcMovementSpeed::UBcMovementSpeed()
{

}

UBcMovementSpeed::~UBcMovementSpeed()
{

}

void UBcMovementSpeed::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::init(bContainer, owner, properties, ownerBuff);
	targetType = bContainer.targetType;
	m_MovementSpeed = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

void UBcMovementSpeed::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::initSim(bContainer, owner, properties, ownerBuff);
	targetType = bContainer.targetType;
	m_MovementSpeed = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

bool UBcMovementSpeed::run(ABaseCharacter* caster, ABaseCharacter* self, int value /*= 0*/)
{
	ABaseCharacter* newTarget = getTarget(caster, self);
	float movementSpeed = 1 + m_MovementSpeed / 100;
	newTarget->applyMovementSpeed(movementSpeed);
	return true;
}

bool UBcMovementSpeed::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	UAISimCharacter* newTarget = getTargetSim(caster, self);
	float movementSpeed = 1 + m_MovementSpeed / 100;
	newTarget->applyMovementSpeed(movementSpeed);
	return true;
}

bool UBcMovementSpeed::isExpired()
{
	return false;
}

void UBcMovementSpeed::update(float deltaTime)
{

}

float UBcMovementSpeed::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	float score = 0.f;
	if (characterState.state == HBCharacterState::MOVEING)
	{

		if (m_MovementSpeed > 0 && (m_properties.targetType == TargetType::SELF || m_properties.targetType == TargetType::SELFFRIEND))
		{
			score = 1.f;
		}
		else if (m_MovementSpeed < 0 && m_properties.targetType == TargetType::ENEMY)
		{
			score = 1.f;
		}
	}
	skillScore->addScore(score, TEXT("movementspeed"));
	return 1.f;
}

float UBcMovementSpeed::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	float score = 0.f;
	if (characterState.state == HBCharacterState::MOVEING)
	{

		if (m_MovementSpeed > 0 && (m_properties.targetType == TargetType::SELF || m_properties.targetType == TargetType::SELFFRIEND))
		{
			score = 1.f;
		}
		else if (m_MovementSpeed < 0 && m_properties.targetType == TargetType::ENEMY)
		{
			score = 1.f;
		}
	}
	skillScore->addScore(score, TEXT("movementspeed"));
	return 1.f;
}
