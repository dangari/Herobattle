// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "SkillEnums.h"

SkillEnums::SkillEnums()
{
}

SkillEnums::~SkillEnums()
{
}


Attributes SkillEnums::stringToAttribute(FString sAttribute)
{
	if (sAttribute.Equals(TEXT("FIRE_MAGIC")))
		return Attributes::FIRE_MAGIC;
	if (sAttribute.Equals(TEXT("HEALING_PRAYERS")))
		return Attributes::HEALING_PRAYERS;
	if (sAttribute.Equals(TEXT("PROTECTION_PRAYERS")))
		return Attributes::PROTECTION_PRAYERS;
	if (sAttribute.Equals(TEXT("STRENGTH")))
		return Attributes::STRENGTH;
	return Attributes::NONE;
}

ProfessionName SkillEnums::stringToProfessionName(FString sProfessionName)
{
	if (sProfessionName.Equals(TEXT("ASSASINE")))
		return ProfessionName::ASSASINE;
	if (sProfessionName.Equals(TEXT("ELEMENTALIST")))
		return ProfessionName::ELEMENTALIST;
	if (sProfessionName.Equals(TEXT("MONK")))
		return ProfessionName::MONK;
	if (sProfessionName.Equals(TEXT("DERWISH")))
		return ProfessionName::DERWISH;
	if (sProfessionName.Equals(TEXT("NEKROMANT")))
		return ProfessionName::NEKROMANT;
	if (sProfessionName.Equals(TEXT("PARAGON")))
		return ProfessionName::PARAGON;
	if (sProfessionName.Equals(TEXT("WARRIOR")))
		return ProfessionName::WARRIOR;
	if (sProfessionName.Equals(TEXT("MESMER")))
		return ProfessionName::MESMER;
	if (sProfessionName.Equals(TEXT("RITUALIST")))
		return ProfessionName::RITUALIST;
	return ProfessionName::NONE;
}

SkillType SkillEnums::stringToSkillType(FString sSkillType)
{
	if (sSkillType.Equals(TEXT("ENTCHANTMENT")))
		return SkillType::ENTCHANTMENT;
	if (sSkillType.Equals(TEXT("ATTACK")))
		return SkillType::ATTACK;
	if (sSkillType.Equals(TEXT("HEX")))
		return SkillType::HEX;
	if (sSkillType.Equals(TEXT("SPELL")))
		return SkillType::SPELL;
	if (sSkillType.Equals(TEXT("HEAL")))
		return SkillType::HEAL;
	return SkillType::SPELL;
}

TargetType SkillEnums::stringToTargetType(FString sTargetType)
{
	if (sTargetType.Equals(TEXT("SELF")))
		return TargetType::SELF;
	if (sTargetType.Equals(TEXT("ENEMY")))
		return TargetType::ENEMY;
	if (sTargetType.Equals(TEXT("FRIEND")))
		return TargetType::FRIEND;
	if (sTargetType.Equals(TEXT("SELFFREND")))
		return TargetType::SELFFREND;
	return
		TargetType::ENEMY;
}

Condition SkillEnums::stringToCondition(FString sCondition)
{
	if (sCondition.Equals(TEXT("BURNING")))
		return Condition::BURNING;
	if (sCondition.Equals(TEXT("BLEEDING")))
		return Condition::BLEEDING;
	if (sCondition.Equals(TEXT("POISEN")))
		return Condition::POISON;
	if (sCondition.Equals(TEXT("DEEPWOUND")))
		return Condition::DEEPWOUND;
	return Condition::BLEEDING;
}
