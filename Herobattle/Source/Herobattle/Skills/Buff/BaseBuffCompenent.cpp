// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseBuffCompenent.h"
#include "XmlParser.h"
#include "Base/BaseCharacter.h"






UBaseBuffCompenent::UBaseBuffCompenent()
{

}

UBaseBuffCompenent::~UBaseBuffCompenent()
{

}

void UBaseBuffCompenent::init(FBuffContainer bContainer, ABaseCharacter* owner)
{

}

bool UBaseBuffCompenent::isExpired()
{
	return false;
}

void UBaseBuffCompenent::update(float deltaTime)
{

}

ABaseCharacter* UBaseBuffCompenent::getTarget(ABaseCharacter* caster, ABaseCharacter* self)
{
	if (targetType == TargetType::SELF)
		return self;
	else if (targetType == TargetType::OWNER)
		return owner;
	else
		return caster;
}

bool UBaseBuffCompenent::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	return true;
}
