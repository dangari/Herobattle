// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcAttackSpeed.h"
#include "AI/AISimCharacter.h"




UBcAttackSpeed::UBcAttackSpeed()
{

}

UBcAttackSpeed::~UBcAttackSpeed()
{

}

void UBcAttackSpeed::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::init(bContainer, owner, properties,ownerBuff);
	targetType = bContainer.targetType;
	m_AttackSpeed = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

void UBcAttackSpeed::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::initSim(bContainer, owner, properties,ownerBuff);
	targetType = bContainer.targetType;
	m_AttackSpeed = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

bool UBcAttackSpeed::run(ABaseCharacter* caster, ABaseCharacter* self, int value /*= 0*/)
{
	ABaseCharacter* newTarget = getTarget(caster, self);
	float attackSpeed = 1 + m_AttackSpeed / 100;
	newTarget->applyAttackSpeed(attackSpeed);
	return true;
}

bool UBcAttackSpeed::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	UAISimCharacter* newTarget = getTargetSim(caster, self);
	float attackSpeed = 1 + m_AttackSpeed / 100;
	newTarget->applyAttackSpeed(attackSpeed);
	return true;
}

bool UBcAttackSpeed::isExpired()
{
	return false;
}

void UBcAttackSpeed::update(float deltaTime)
{

}

float UBcAttackSpeed::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	float score = 0.f;
	if (characterState.state == HBCharacterState::AUTOATTACK)
	{

		if (m_AttackSpeed > 0 && (m_properties.targetType == TargetType::SELF || m_properties.targetType == TargetType::SELFFRIEND))
		{
			score = 1.f;
		}
		else if (m_AttackSpeed < 0 && m_properties.targetType == TargetType::ENEMY)
		{
			score = 1.f;
		}
	}
	skillScore->addScore(score, TEXT("attackspeed"));
	return 1.f;
}

float UBcAttackSpeed::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	float score = 0.f;
	if (characterState.state == HBCharacterState::AUTOATTACK)
	{

		if (m_AttackSpeed > 0 && (m_properties.targetType == TargetType::SELF || m_properties.targetType == TargetType::SELFFRIEND))
		{
			score = 1.f;
		}
		else if (m_AttackSpeed < 0 && m_properties.targetType == TargetType::ENEMY)
		{
			score = 1.f;
		}
	}
	skillScore->addScore(score, TEXT("attackspeed"));
	return 1.f;
}
