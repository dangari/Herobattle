// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScDamage.h"
#include "../../Base/BaseCharacter.h"

UScDamage::UScDamage()
{
	//damageType = HBDamageType::FIRE;
}


UScDamage::~UScDamage()
{
}


void UScDamage::run(ABaseCharacter* target, ABaseCharacter* self)
{
	Super::run(target, self);
	float damage = scaleTable[self->getAttributeValue(scaleAttribute)];
	//target->damage(damage, damageType);
}

float UScDamage::getScore()
{
	return 1.f;
}

void UScDamage::init(FXmlNode* node)
{
//	throw std::logic_error("The method or operation is not implemented.");
}

