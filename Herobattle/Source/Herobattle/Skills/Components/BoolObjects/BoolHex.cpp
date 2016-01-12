// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolHex.h"




UBoolHex::UBoolHex()
{

}

UBoolHex::~UBoolHex()
{

}

bool UBoolHex::test(ABaseCharacter* target, ABaseCharacter* self)
{
	ABaseCharacter* newTarget = getTarget(target, self);
	if (newTarget->getDebuffCount() > 0)
		return true;
	else
		return false;
}

bool UBoolHex::testSim(UAISimCharacter* target, UAISimCharacter* self)
{
	UAISimCharacter* newTarget = getTargetSim(target, self);
	if (newTarget->getDebuffCount() > 0)
		return true;
	else
		return false;
}

void UBoolHex::init(FXmlNode* node, ComponentTarget target)
{
	targetType = target;
}
