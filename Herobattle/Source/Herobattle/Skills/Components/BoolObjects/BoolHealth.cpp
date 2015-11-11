// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolHealth.h"
#include "../../../Base/BaseCharacter.h"


BoolHealth::BoolHealth()
{
}

BoolHealth::~BoolHealth()
{
}

bool BoolHealth::test(ABaseCharacter* target, ABaseCharacter* self)
{
	bool test;
	ABaseCharacter* testTarget;
	if (targetType == TargetType::SELF)
		testTarget = self;
	else
		testTarget = target;

	float healthPrec = (testTarget->m_MaxHealth / testTarget->m_MaxHealth) * 100;
	if (c.Equals(TEXT("-")))
	{
		test = healthPrec < treshold;
	}
	else
	{
		test = healthPrec > treshold;
	}
	return test;
}

void BoolHealth::init(FXmlNode* node, TargetType target)
{
	this->targetType = target;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("whencondition")))
	{
		treshold = FCString::Atoi(*(node->GetAttribute(TEXT("value"))));
		c = node->GetAttribute(TEXT("type"));
	}

}