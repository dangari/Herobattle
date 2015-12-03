// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScDamage.h"
#include "../../Base/BaseCharacter.h"
UScDamage::UScDamage()
{
	FString name = TEXT("Damage");
}


UScDamage::~UScDamage()
{
}


bool UScDamage::run(ABaseCharacter* target, ABaseCharacter* self)
{
	ABaseCharacter* testTarget;
	if (targetType == TargetType::SELF)
		testTarget = self;
	else
		testTarget = target;
	Super::run(target, self);
	float damage = scaleTable[self->getAttributeValue(scaleAttribute)];
	target->damage(self, damage, damageType);
	return true;
}

float UScDamage::getScore(FCharacterState characterState)
{
	return 1.f;
}

void UScDamage::init(FXmlNode* node)
{
	targetType = SkillEnums::stringToTargetType(node->GetAttribute("target"));
	FString cType = node->GetAttribute(TEXT("type"));
	this->damageType = SkillEnums::stringToHBDamageType(cType);
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("damage")))
	{
		fillScaleTable(node);
	}

}

