// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcGiveMana.h"
#include "Base/BaseCharacter.h"
#include "AI/SkillScore.h"
#include "AI/AISimCharacter.h"
#include "Buff.h"



UBcGiveMana::UBcGiveMana()
{

}

UBcGiveMana::~UBcGiveMana()
{

}

bool UBcGiveMana::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	ABaseCharacter* newTarget = getTarget(caster, self);
	newTarget->ChangeMana(m_ManaFactor);
	return true;
}

bool UBcGiveMana::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	UAISimCharacter* newTarget = getTargetSim(caster, self);
	newTarget->ChangeMana(m_ManaFactor);
	return true;
}

float UBcGiveMana::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	int mana = m_ManaFactor;
	ABaseCharacter* newTarget = getTarget(characterState.self, caster);
	float score;
	if (caster->ETeam == characterState.ETeam)
	{
		int missingMana = newTarget->m_MaxMana - newTarget->m_MaxMana;
		score = missingMana / mana;
		if (score > 1.f)
			score = 1.f;
		if (score < 0.f)
			score = 0.f;
	}
	else
	{
		if (mana < treshhold)
		{
			score = mana / treshhold;
		}
		else
		{
			score = 1.f;
		}
		if (score > 0)
			skillScore->addScore(score, TEXT("givemana"));
	}
	return 1.f;
}

float UBcGiveMana::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	int mana = m_ManaFactor;
	//UAISimCharacter* newTarget = getTargetSim(characterState.self, caster);
	float score;
	/*if (caster->ETeam == characterState.ETeam)
	{
		int missingMana = newTarget->m_MaxMana - newTarget->m_MaxMana;
		score = missingMana / mana;
		if (score > 1.f)
			score = 1.f;
		if (score < 0.f)
			score = 0.f;
	}
	else
	{*/
		if (mana < treshhold)
		{
			score = mana / treshhold;
		}
		else
		{
			score = 1.f;
		}
		if (score > 0)
			skillScore->addScore(score, TEXT("givemana"));
	//}
	return 1.f;
}

void UBcGiveMana::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::init(bContainer, owner, properties, ownerBuff);
	FString tagName = bContainer.node->GetTag();
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_ManaFactor = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

void UBcGiveMana::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::initSim(bContainer, owner, properties, ownerBuff);
	FString tagName = bContainer.node->GetTag();
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_ManaFactor = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

bool UBcGiveMana::isExpired()
{
	return false;
}

FString UBcGiveMana::ToString()
{
	FString sCText = TEXT("mana");
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());

	return sCText;
}
