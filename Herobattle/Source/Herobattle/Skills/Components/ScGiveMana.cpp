// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScGiveMana.h"




UScGiveMana::UScGiveMana()
{

}

UScGiveMana::~UScGiveMana()
{

}

bool UScGiveMana::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	ABaseCharacter* newTarget = getTarget(target, self);
	newTarget->ChangeMana(scaleTable[self->getAttributeValue(scaleAttribute)]);
	return true;
}

bool UScGiveMana::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	UAISimCharacter* newTarget = getTargetSim(target, self);
	newTarget->ChangeMana(scaleTable[self->getAttributeValue(scaleAttribute)]);
	return true;
}

float UScGiveMana::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	int mana = scaleTable[caster->getAttributeValue(scaleAttribute)];
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

float UScGiveMana::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	int mana = scaleTable[caster->getAttributeValue(scaleAttribute)];
	float score;
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
	return 1.f;
}

void UScGiveMana::init(FXmlNode* node, FSkillProperties properties)
{
	Super::init(node, properties);
	FString tagName = node->GetTag();
	targetType = SkillEnums::stringToComponentTarget(node->GetAttribute(TEXT("target")));
	if (tagName.Equals(TEXT("givemana")))
	{
		fillScaleTable(node);
	}
}

FString UScGiveMana::ToString()
{
	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());

	return sCText;
}
