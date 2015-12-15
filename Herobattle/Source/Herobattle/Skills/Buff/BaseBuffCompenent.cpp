// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseBuffCompenent.h"
#include "XmlParser.h"
#include "Base/BaseCharacter.h"
#include "AI/CharacterState.h"






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

float UBaseBuffCompenent::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	return 1.f;
}

FString UBaseBuffCompenent::ToString()
{
	return TEXT("");
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
