// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolHealth.h"
#include "../../../Base/BaseCharacter.h"


UBoolHealth::UBoolHealth()
{
}

UBoolHealth::~UBoolHealth()
{
}

bool UBoolHealth::test(ABaseCharacter* target, ABaseCharacter* self)
{
	bool test;
	ABaseCharacter* testTarget = getTarget(target, self);

	float healthPrec = (testTarget->m_Health / testTarget->m_MaxHealth) * 100;
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

void UBoolHealth::init(FXmlNode* node, ComponentTarget target)
{
	targetType = target;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	
	name = node->GetTag();
	if (name.Equals(TEXT("hp")))
	{
		treshold = FCString::Atoi(*(node->GetAttribute(TEXT("value"))));
		c = node->GetAttribute(TEXT("type"));
	}

}