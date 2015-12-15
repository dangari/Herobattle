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
	if (sAttribute.Equals(TEXT("ENERGY_STORAGE")))
		return Attributes::ENERGY_STORAGE;
	if (sAttribute.Equals(TEXT("EARTH_PRAYERS")))
		return Attributes::EARTH_PRAYERS;
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
	if (sSkillType.Equals(TEXT("ATTACK")))
		return SkillType::ATTACK;
	if (sSkillType.Equals(TEXT("ENTCHANTMENT")))
		return SkillType::ENTCHANTMENT;
	if (sSkillType.Equals(TEXT("RANGEATTACK")))
		return SkillType::RANGEATTACK;
	if (sSkillType.Equals(TEXT("MELEEATTACK")))
		return SkillType::MELEEATTACK;
	if (sSkillType.Equals(TEXT("HEX")))
		return SkillType::HEX;
	if (sSkillType.Equals(TEXT("SPELL")))
		return SkillType::SPELL;
	if (sSkillType.Equals(TEXT("HEAL")))
		return SkillType::HEAL;
	if (sSkillType.Equals(TEXT("UNIQUE_BUFF")))
		return SkillType::UNIQUE_BUFF;
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
	if (sTargetType.Equals(TEXT("SELFFRIEND")))
		return TargetType::SELFFRIEND;
	if (sTargetType.Equals(TEXT("OWNER")))
		return TargetType::OWNER;
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
	if (sCondition.Equals(TEXT("CRIPPLED")))
		return Condition::CRIPPLED;
	return Condition::ALL;
}

HBDamageType SkillEnums::stringToHBDamageType(FString sHBDamageType)
{
	if (sHBDamageType.Equals(TEXT("FIRE")))
		return HBDamageType::FIRE;
	if (sHBDamageType.Equals(TEXT("PHYSICAL")))
		return HBDamageType::PHYSICAL;
	if (sHBDamageType.Equals(TEXT("WATER")))
		return HBDamageType::WATER;
	if (sHBDamageType.Equals(TEXT("LIGHTNING")))
		return HBDamageType::LIGHTNING;
	return HBDamageType::PHYSICAL;
}

Trigger SkillEnums::stringToTrigger(FString sTrigger)
{
	if (sTrigger.Equals(TEXT("DAMAGE")))
		return Trigger::DAMAGE;
	if (sTrigger.Equals(TEXT("HEAL")))
		return Trigger::HEAL;
	if (sTrigger.Equals(TEXT("HIT")))
		return Trigger::HIT;
	if (sTrigger.Equals(TEXT("AFTERCAST")))
		return Trigger::AFTERCAST;
	if (sTrigger.Equals(TEXT("CASTMANA")))
		return Trigger::CASTMANA;
	return Trigger::HEAL;
}

ComponentTarget SkillEnums::stringToComponentTarget(FString sComponentTarget)
{
	if (sComponentTarget.Equals(TEXT("TARGET")))
		return ComponentTarget::TARGET;
	if (sComponentTarget.Equals(TEXT("SELF")))
		return ComponentTarget::SELF;
	return ComponentTarget::TARGET;
}

CoolDownType SkillEnums::stringToCoolDownType(FString sCoolDownType)
{

	if (sCoolDownType.Equals(TEXT("ALL")))
		return CoolDownType::ALL;
	if (sCoolDownType.Equals(TEXT("INTERRUPT")))
		return CoolDownType::INTERRUPT;
	if (sCoolDownType.Equals(TEXT("CURRENTSKILL")))
		return CoolDownType::CURRENTSKILL;
	if (sCoolDownType.Equals(TEXT("ATTRIBUTE")))
		return CoolDownType::ATTRIBUTE;
	return CoolDownType::CURRENTSKILL;
}

FString SkillEnums::AttributesToString(Attributes attribute)
{
	switch (attribute)
	{
	case Attributes::NONE:
		return TEXT("NONE");
	case Attributes::FIRE_MAGIC:
		return TEXT("FIRE_MAGIC");
	case Attributes::HEALING_PRAYERS:
		return TEXT("HEALING_PRAYERS");
	case Attributes::PROTECTION_PRAYERS:
		return TEXT("PROTECTION_PRAYERS");
	case Attributes::STRENGTH:
		return TEXT("STRENGTH");
	default:
		return TEXT("NONE");

	}
}

