// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScCoolDown.h"
#include "Base/BaseCharacter.h"
#include "AI/AISimCharacter.h"
#include "AI/SkillScore.h"



UScCoolDown::UScCoolDown()
{
	componentName = TEXT("cooldown");
}

UScCoolDown::~UScCoolDown()
{

}

bool UScCoolDown::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	ABaseCharacter* newTarget = getTarget(target, self);
	float time = scaleTable[self->getAttributeValue(scaleAttribute)];
	newTarget->setCoolDown(time, coolDownType);
	return true;
}

bool UScCoolDown::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	UAISimCharacter* newTarget = getTargetSim(target, self);
	float time = scaleTable[self->getAttributeValue(scaleAttribute)];
	newTarget->setCoolDown(time, coolDownType);
	return true;
}

float UScCoolDown::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float score =0.f;
	if (scaleAttribute == Attributes::NONE)
	{
		score = 1.f;
	}
	else
	{
		int attValue = caster->getAttributeValue(scaleAttribute);
		float score = attValue / 14.f;
		if (score > 0.5)
			score = 1.f;
		else
			score = score;
	}

	skillScore->addScore(score, componentName);
	return score;
}

float UScCoolDown::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float score = 0.f;
	if (scaleAttribute == Attributes::NONE)
	{
		score = 1.f;
	}
	else
	{
		int attValue = caster->getAttributeValue(scaleAttribute);
		float score = attValue / 14.f;
		if (score > 0.5)
			score = 1.f;
		else
			score = score;
	}

	skillScore->addScore(score, componentName);
	return score;
}

void UScCoolDown::init(FXmlNode* node, FSkillProperties properties)
{
	Super::init(node, properties);
	targetType = SkillEnums::stringToComponentTarget(node->GetAttribute("target"));
	coolDownType = SkillEnums::stringToCoolDownType(node->GetAttribute("type"));
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("damage")))
	{
		fillScaleTable(node);
	}
}

FString UScCoolDown::ToString()
{

	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());

	return sCText;

}
