// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScBuff.h"
#include "../../Base/BaseCharacter.h"
UScBuff::UScBuff()
{
	//damageType = HBDamageType::FIRE;
}


UScBuff::~UScBuff()
{
}


void UScBuff::run(ABaseCharacter* target, ABaseCharacter* self)
{
	Super::run(target, self);
	float damage = scaleTable[self->getAttributeValue(scaleAttribute)];
	//target->damage(damage, damageType);
}

float UScBuff::getScore()
{
	return 1.f;
}

void UScBuff::init(FXmlNode* node)
{
	FString cType = node->GetAttribute(TEXT("type"));
	this->damageType = SkillEnums::stringToHBDamageType(cType);
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("damage")))
	{
		fillScaleTable(node);
	}
}

