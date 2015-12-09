// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScKnockDown.h"
#include "Base/BaseCharacter.h"
#include "AI/SkillScore.h"



UScKnockDown::UScKnockDown()
{
	componentName = TEXT("KnockDown");
}

UScKnockDown::~UScKnockDown()
{

}

bool UScKnockDown::run(ABaseCharacter* target, ABaseCharacter* self)
{
	ABaseCharacter* testTarget = getTarget(target, self);

	testTarget->knockDownCharacter(scaleTable[target->getAttributeValue(scaleAttribute)]);
	return true;
}

void UScKnockDown::init(FXmlNode* node)
{
	targetType = SkillEnums::stringToComponentTarget(node->GetAttribute("target"));
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("knockdown")))
	{
		fillScaleTable(node);
	}
}

float UScKnockDown::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	return 0.f;
}

FString UScKnockDown::ToString()
{
	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());

	return sCText;
}

