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
	float healthPrec = (target->m_MaxHealth / target->m_MaxHealth) * 100;
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
	this->target = target;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	for (auto& prop : propertyList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("whencondition")))
		{
			treshold = FCString::Atoi(*(prop->GetAttribute(TEXT("value"))));
			c = prop->GetAttribute(TEXT("type"));
		}
	}
}