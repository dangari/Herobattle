// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScRemove.h"
#include "Base/BaseCharacter.h"
#include "AI/AISimCharacter.h"
#include "AI/SkillScore.h"



UScRemove::UScRemove()
{
	componentName = TEXT("REmove");
}

UScRemove::~UScRemove()
{

}

bool UScRemove::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	int count = scaleTable[self->getAttributeValue(scaleAttribute)];
	ABaseCharacter* newTarget = getTarget(target, self);
	newTarget->Remove(rType, count);
	return true;
}

bool UScRemove::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	int count = scaleTable[self->getAttributeValue(scaleAttribute)];
	UAISimCharacter* newTarget = getTargetSim(target, self);
	newTarget->Remove(rType, count);
	return true;
}

float UScRemove::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float score = 0.f;
	switch (rType)
	{
	case RemoveType::HEX:
		if (characterState.isHexed)
			score = 1.f;
		break;
	case RemoveType::ENTCHANTMENT:
		if (characterState.isBuffed)
			score = 1.f;
		break;
	case RemoveType::STANCE:
		if (characterState.hasStance)
			score = 1.f;
		break;
	case RemoveType::CONDI:
		if (characterState.conditions.Num() > 0)
		{
			int count = scaleTable[caster->getAttributeValue(scaleAttribute)];
			score = characterState.conditions.Num() / count;
		}
		break;
	default:
		break;
	}
	skillScore->addScore(score, componentName);
	return 1.f;

	
}

float UScRemove::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float score = 0.f;
	switch (rType)
	{
	case RemoveType::HEX:
		if (characterState.isHexed)
			score = 1.f;
		break;
	case RemoveType::ENTCHANTMENT:
		if (characterState.isBuffed)
			score = 1.f;
		break;
	case RemoveType::STANCE:
		if (characterState.hasStance)
			score = 1.f;
		break;
	case RemoveType::CONDI:
		if (characterState.conditions.Num() > 0)
		{
			int count = scaleTable[caster->getAttributeValue(scaleAttribute)];
			score = characterState.conditions.Num() / count;
			if (score > 1)
				score = 1.f;
		}
		break;
	default:
		break;
	}
	skillScore->addScore(score, componentName);
	return 1.f;
}

void UScRemove::init(FXmlNode* node, FSkillProperties properties)
{
	Super::init(node, properties);
	targetType = SkillEnums::stringToComponentTarget(node->GetAttribute("target"));
	rType = SkillEnums::stringToRemoveType(node->GetAttribute(TEXT("type")));
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("remove")))
	{
		fillScaleTable(node);
	}
}

FString UScRemove::ToString()
{
	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());

	return sCText;
}
