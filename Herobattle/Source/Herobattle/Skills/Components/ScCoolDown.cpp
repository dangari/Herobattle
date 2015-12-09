// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScCoolDown.h"
#include "AI/SkillScore.h"




UScCoolDown::UScCoolDown()
{
	componentName = TEXT("Damage");
}

UScCoolDown::~UScCoolDown()
{

}

bool UScCoolDown::run(ABaseCharacter* target, ABaseCharacter* self)
{
	ABaseCharacter* newTarget = getTarget(target, self);
	float time = scaleTable[self->getAttributeValue(scaleAttribute)];
	newTarget->setCoolDown(time, coolDownType);
	return true;
}

float UScCoolDown::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	if (scaleAttribute == Attributes::NONE)
	{
		return 1.f;
	}
	else
	{
		int attValue = caster->getAttributeValue(scaleAttribute);
		float score = attValue / 14.f;
		if (score > 0.5)
			return 1.f;
		else
			return score;
	}
}

void UScCoolDown::init(FXmlNode* node)
{
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
