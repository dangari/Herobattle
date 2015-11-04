// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScWhenCondition.h"
#include "BoolObjects/BoolObject.h"


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
//	throw std::logic_error("The method or operation is not implemented.");
}
