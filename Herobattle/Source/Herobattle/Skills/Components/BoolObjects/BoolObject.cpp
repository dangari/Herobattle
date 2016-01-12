// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolObject.h"
#include "../../../Base/BaseCharacter.h"
#include "AI/AISimCharacter.h"


UBoolObject::UBoolObject()
{
}

UBoolObject::~UBoolObject()
{
}

bool UBoolObject::test(ABaseCharacter* target, ABaseCharacter* self)
{
	return true;
}

bool UBoolObject::testSim(UAISimCharacter* target, UAISimCharacter* self)
{
	return true;
}

void UBoolObject::init(FXmlNode* node, ComponentTarget target)
{

}

ABaseCharacter* UBoolObject::getTarget(ABaseCharacter* target, ABaseCharacter* self)
{
	if (targetType == ComponentTarget::SELF)
	{
		return self;
	}
	else
	{
		return target;
	}
}

UAISimCharacter* UBoolObject::getTargetSim(UAISimCharacter* target, UAISimCharacter* self)
{
	if (targetType == ComponentTarget::SELF)
	{
		return self;
	}
	else
	{
		return target;
	}
}
