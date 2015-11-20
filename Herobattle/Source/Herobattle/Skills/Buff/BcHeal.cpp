// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcHeal.h"
#include "Base/BaseCharacter.h"
#include "Enum/SkillEnums.h"





UBcHeal::UBcHeal()
{

}

UBcHeal::~UBcHeal()
{

}

void UBcHeal::init(FBuffContainer bContainer, ABaseCharacter* owner)
{
	targetType = bContainer.targetType;
	heal = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
	trigger = SkillEnums::stringToTrigger(bContainer.node->GetAttribute(TEXT("trigger")));
}

bool UBcHeal::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	if ((value < 0 && trigger == Trigger::DAMAGE) || value > 0 && trigger == Trigger::HEAL)
	{
		ABaseCharacter* testTarget;
		if (targetType == TargetType::SELF)
			testTarget = self;
		else
			testTarget = caster;
		testTarget->heal(testTarget, heal, false);
	}
	return true;
}

bool UBcHeal::isExpired()
{
	return false;
}

void UBcHeal::update(float deltaTime)
{

}
