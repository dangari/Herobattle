// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScKnockDown.h"
#include "Base/BaseCharacter.h"




UScKnockDown::UScKnockDown()
{

}

UScKnockDown::~UScKnockDown()
{

}

bool UScKnockDown::run(ABaseCharacter* target, ABaseCharacter* self)
{
	ABaseCharacter* testTarget;
	if (targetType == TargetType::SELF)
		testTarget = self;
	else
		testTarget = target;

	testTarget->knockDownCharacter(scaleTable[target->getAttributeValue(scaleAttribute)]);
	return true;
}

void UScKnockDown::init(FXmlNode* node)
{
	targetType = SkillEnums::stringToTargetType(node->GetAttribute("target"));
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("knockdown")))
	{
		fillScaleTable(node);
	}
}

float UScKnockDown::getScore(FCharacterState characterState)
{
	return 0.f;
}
