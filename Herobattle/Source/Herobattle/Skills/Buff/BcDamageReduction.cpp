// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcDamageReduction.h"
#include "AI/AISimCharacter.h"




UBcDamageReduction::UBcDamageReduction()
{

}

UBcDamageReduction::~UBcDamageReduction()
{

}

bool UBcDamageReduction::run(ABaseCharacter* caster, ABaseCharacter* self, int value /*= 0*/)
{
	float reduction = 0.f;
	if (m_RType == ReductionType::VALUE)
	{
		reduction = m_Reduction;
	}
	else
	{
		reduction = m_Reduction * value;
	}
	ABaseCharacter* newTarget = getTarget(caster, self);
	newTarget->applyDamageReduction(reduction);

	return true;
}

bool UBcDamageReduction::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	float reduction = 0.f;
	if (m_RType == ReductionType::VALUE)
	{
		reduction = m_Reduction;
	}
	else
	{
		reduction = m_Reduction * value;
	}
	UAISimCharacter* newTarget = getTargetSim(caster, self);
	newTarget->applyDamageReduction(reduction);

	return true;
}

void UBcDamageReduction::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties)
{
	Super::initSim(bContainer, owner, properties);
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_Reduction = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
	m_RType = SkillEnums::stringTReductionType(bContainer.node->GetAttribute(TEXT("type")));
}

float UBcDamageReduction::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 0.0f;
}

float UBcDamageReduction::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 0.0f;
}

void UBcDamageReduction::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties)
{
	Super::init(bContainer, owner, properties);
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_Reduction = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
	m_RType = SkillEnums::stringTReductionType(bContainer.node->GetAttribute(TEXT("type")));
}

bool UBcDamageReduction::isExpired()
{
	return false;
}

FString UBcDamageReduction::ToString()
{
	return Super::ToString();
}
