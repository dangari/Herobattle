// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScKnockDown.h"
#include "Base\BaseCharacter.h"




UScKnockDown::UScKnockDown()
{

}

UScKnockDown::~UScKnockDown()
{

}

bool UScKnockDown::run(ABaseCharacter* target, ABaseCharacter* self)
{
	target->knockDownCharacter(scaleTable[target->getAttributeValue(scaleAttribute)]);
}

void UScKnockDown::init(FXmlNode* node)
{

}

float UScKnockDown::getScore()
{
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("knockdown")))
	{
		fillScaleTable(node);
	}
}
