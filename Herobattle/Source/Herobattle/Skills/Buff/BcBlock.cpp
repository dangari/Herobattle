// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcBlock.h"




UBcBlock::UBcBlock()
{

}

UBcBlock::~UBcBlock()
{

}

void UBcBlock::init(FBuffContainer bContainer, ABaseCharacter* owner)
{
	FXmlNode* node = bContainer.node;
	FString sUsage = node->GetAttribute(TEXT("usage"));
	if (sUsage.Equals(TEXT("INF")))
	{
		haveUsages = false;
	}
	else
	{
		haveUsages = true;
		usage = FCString::Atoi(*sUsage);
	}
	blockChance = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

bool UBcBlock::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	return true;
}

bool UBcBlock::isExpired()
{
	if (haveUsages)
	{
		if (usage > 0)
			return true;
	}
	return false;
}

void UBcBlock::update(float deltaTime)
{

}
