// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolCondition.h"
#include "../../../Base/BaseCharacter.h"


UBoolCondition::UBoolCondition()
{
}

UBoolCondition::~UBoolCondition()
{
}

bool UBoolCondition::test(ABaseCharacter* target, ABaseCharacter* self)
{
	ABaseCharacter* testTarget = getTarget(target, self);

	int cCount = testTarget->getCondtionCount();
	if (cCount > 0)
	{
		if (cType == Condition::ALL)
			return true;
		if (testTarget->hasCondition(cType))
			return true;
		else
			return false;
	}
	return false;

}

void UBoolCondition::init(FXmlNode* node, ComponentTarget target)
{
	targetType = target;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	
	name = node->GetTag();
	if (name.Equals(TEXT("condi")))
	{
		cType = SkillEnums::stringToCondition(node->GetAttribute(TEXT("type")));
	}

}