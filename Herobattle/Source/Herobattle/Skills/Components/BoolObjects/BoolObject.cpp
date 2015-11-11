// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolObject.h"
#include "../../../Base/BaseCharacter.h"


BoolObject::BoolObject()
{
}

BoolObject::~BoolObject()
{
}

bool BoolObject::test(ABaseCharacter* target, ABaseCharacter* self)
{
	return true;
}

void BoolObject::init(FXmlNode* node, TargetType target)
{

}