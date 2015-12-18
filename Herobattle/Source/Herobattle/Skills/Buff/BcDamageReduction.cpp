// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcDamageReduction.h"




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
		reduction = m_Reduction - value;
		if (reduction < 0)
			reduction = m_Reduction;
	}
	else
	{
		reduction = m_Reduction * value;
	}
	ABaseCharacter* newTarget = getTarget(caster, self);
	newTarget->heal(newTarget, reduction, false);

	return true;
}

float UBcDamageReduction::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 0.0f;
}

void UBcDamageReduction::init(FBuffContainer bContainer, ABaseCharacter* owner)
{
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
