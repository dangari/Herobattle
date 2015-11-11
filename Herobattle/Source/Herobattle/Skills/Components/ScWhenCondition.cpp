// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScWhenCondition.h"
#include "BoolObjects/BoolObject.h"
#include "BoolObjects/BoolHealth.h"


UScWhenCondition::UScWhenCondition()
{
	//damageType = HBDamageType::FIRE;
}


UScWhenCondition::~UScWhenCondition()
{
}


void UScWhenCondition::run(ABaseCharacter* target, ABaseCharacter* self)
{
	if (testConditions(target, self))
	{
		for (auto& sc : scTable)
		{
			sc->run(target, self);
		}
	}
}

float UScWhenCondition::getScore()
{
	return 1.f;
}

bool UScWhenCondition::testConditions(ABaseCharacter* target, ABaseCharacter* self)
{
	for (auto& bo : boolObjects)
	{
		if (bo->test(target, self) == false)
		{
			return false;
		}
	}
	return true;
}

void UScWhenCondition::init(FXmlNode* node)
{
	FString cType = node->GetAttribute(TEXT("type"));
	this->targetType = SkillEnums::stringToTargetType(cType);
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	for (auto& prop : propertyList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("whencondition")))
		{
			createBoolObjects(prop);

		}
	}
}

void UScWhenCondition::createBoolObjects(FXmlNode* prop)
{
	TArray<FXmlNode*> boolObjectList = prop->GetChildrenNodes();
	for (auto& prop : boolObjectList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("hp")))
		{
			BoolHealth* hpBool = NewObject<BoolHealth>();
			hpBool->init(prop, targetType);
			boolObjects.Add(hpBool);
		}
	}
}