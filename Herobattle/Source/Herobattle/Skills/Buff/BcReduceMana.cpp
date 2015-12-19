// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcReduceMana.h"




UBcReduceMana::UBcReduceMana()
{

}

UBcReduceMana::~UBcReduceMana()
{

}

void UBcReduceMana::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties)
{
	Super::init(bContainer, owner, properties);
	reduction = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

bool UBcReduceMana::run(ABaseCharacter* caster, ABaseCharacter* self, int value /*= 0*/)
{
	ABaseCharacter* newTarget = getTarget(caster, self);
	newTarget->applyManaReduction(reduction);
	return true;
}

bool UBcReduceMana::isExpired()
{
	return false;
}

void UBcReduceMana::update(float deltaTime)
{

}
