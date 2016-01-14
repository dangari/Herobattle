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

void UBcHeal::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::init(bContainer, owner, properties, ownerBuff);
	targetType = bContainer.targetType;
	heal = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
	trigger = SkillEnums::stringToTrigger(bContainer.node->GetAttribute(TEXT("trigger")));
}

void UBcHeal::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::initSim(bContainer, owner, properties, ownerBuff);
	targetType = bContainer.targetType;
	heal = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
	trigger = SkillEnums::stringToTrigger(bContainer.node->GetAttribute(TEXT("trigger")));
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

bool UBcHeal::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	if ((value < 0 && trigger == Trigger::DAMAGE) || value > 0 && trigger == Trigger::HEAL)
	{
		UAISimCharacter* testTarget = getTargetSim(caster, self);
		testTarget->heal(testTarget, heal, false);
	}
	if (Trigger::CASTMANA == trigger)
	{
		UAISimCharacter* testTarget = getTargetSim(caster, self);
		float currentHeal = testTarget->currentSkill.skill->properties.cost * (heal / 100);
		testTarget->heal(testTarget, currentHeal, false);
	}
	return true;
}

float UBcHeal::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 1.f;
}

float UBcHeal::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	return 1.f;
}

bool UBcHeal::isExpired()
{
	return false;
}

void UBcHeal::update(float deltaTime)
{

}
