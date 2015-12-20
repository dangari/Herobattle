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

void UBcHeal::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties)
{
	Super::init(bContainer, owner, properties);
	targetType = bContainer.targetType;
	heal = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
	trigger = SkillEnums::stringToTrigger(bContainer.node->GetAttribute(TEXT("trigger")));
	this->owner = owner;
}

bool UBcHeal::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	if ((value < 0 && trigger == Trigger::DAMAGE) || value > 0 && trigger == Trigger::HEAL)
	{
		ABaseCharacter* testTarget = getTarget(caster, self);
		testTarget->heal(testTarget, heal, false);
	}
	if (Trigger::CASTMANA == trigger)
	{
		ABaseCharacter* testTarget = getTarget(caster, self);
		float currentHeal = testTarget->currentSkill.skill->properties.cost * (heal / 100);
		testTarget->heal(testTarget, currentHeal, false);
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
