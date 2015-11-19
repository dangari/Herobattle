// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseBuffCompenent.h"
#include "XmlParser.h"
#include "Base/BaseCharacter.h"






void UBaseBuffCompenent::init(FXmlNode* node, ABaseCharacter* owner)
{

}

bool UBaseBuffCompenent::isExpired()
{
	return false;
}

bool UBaseBuffCompenent::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	return true;
}
