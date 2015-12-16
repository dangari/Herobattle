// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcGiveManaValue.h"




UBcGiveManaValue::UBcGiveManaValue()
{

}

UBcGiveManaValue::~UBcGiveManaValue()
{

}

bool UBcGiveManaValue::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	ABaseCharacter* newTarget = getTarget(caster, self);
	if (m_CostType == CostType::MANA)
	{
		int manacost = newTarget->currentSkill.skill->manaCost;
		int mana = FPlatformMath::RoundToInt((m_ManaFactor / 100)*manacost);
		newTarget->ChangeMana(mana);
	}
	return true;
}

float UBcGiveManaValue::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float score = 1.f;
	skillScore->addScore(score, TEXT("givemana"));
	return 1.f;
}

void UBcGiveManaValue::init(FBuffContainer bContainer, ABaseCharacter* owner)
{
	FString tagName = bContainer.node->GetTag();
	m_CostType = SkillEnums::stringToCostType(bContainer.node->GetAttribute(TEXT("type")));
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_ManaFactor = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

bool UBcGiveManaValue::isExpired()
{
	return false;
}

FString UBcGiveManaValue::ToString()
{
	FString sCText = TEXT("mana");
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());

	return sCText;
}
