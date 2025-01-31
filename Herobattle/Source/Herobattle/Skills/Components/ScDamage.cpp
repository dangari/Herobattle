// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "ScDamage.h"
#include "../../Base/BaseCharacter.h"
#include "Base/BaseCharacter.h"
#include "AI/AISimCharacter.h"
#include "AI/SkillScore.h"

UScDamage::UScDamage()
{
	componentName = TEXT("Damage");
}


UScDamage::~UScDamage()
{
}


bool UScDamage::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	ABaseCharacter* testTarget = getTarget(target,self);
	Super::run(target, self);
	float damage = scaleTable[self->getAttributeValue(scaleAttribute)];
	if (m_properties.skillType == SkillType::MELEEATTACK || (m_properties.skillType == SkillType::RANGEATTACK))
	{
		FWeaponValues weapon(m_properties.weaponType);
		damage += weapon.getDamage();
	}
	target->damage(self, damage, damageType);
	return true;
}

bool UScDamage::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	UAISimCharacter* testTarget = getTargetSim(target, self);
	float damage = scaleTable[self->getAttributeValue(scaleAttribute)];
	if (m_properties.skillType == SkillType::MELEEATTACK || (m_properties.skillType == SkillType::RANGEATTACK))
	{
		FWeaponValues weapon(m_properties.weaponType);
		damage += weapon.getDamage();
	}
	target->damage(self, damage, damageType);
	return true;
}

float UScDamage::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float damage = scaleTable[caster->getAttributeValue(scaleAttribute)];
	skillScore->addDamage(damage, targetType);
	return 1.f;
}

float UScDamage::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	float damage = scaleTable[caster->getAttributeValue(scaleAttribute)];
	skillScore->addDamage(damage, targetType);
	return 1.f;
}

void UScDamage::init(FXmlNode* node, FSkillProperties properties)
{
	Super::init(node, properties);
	targetType = SkillEnums::stringToComponentTarget(node->GetAttribute("target"));
	FString cType = node->GetAttribute(TEXT("type"));
	this->damageType = SkillEnums::stringToHBDamageType(cType);
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("damage")))
	{
		fillScaleTable(node);
	}

}

FString UScDamage::ToString()
{

	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());
	
	return sCText;

}

