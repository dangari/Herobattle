// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

UENUM(BlueprintType)
enum class Attributes : uint8{ NONE, FIRE_MAGIC, HEALING_PRAYERS, PROTECTION_PRAYERS, STRENGTH, ENERGY_STORAGE, EARTH_PRAYERS, TACTICS, SPEAR_MASTERY};

UENUM(BlueprintType)
enum class ProfessionName : uint8{NONE, ASSASINE, ELEMENTALIST, MONK, DERWISH, NEKROMANT, PARAGON, WARRIOR, MESMER, RITUALIST };

UENUM(BlueprintType)
enum class SkillType : uint8{ATTACK, ENTCHANTMENT, RANGEATTACK,MELEEATTACK , HEX, SPELL, HEAL, UNIQUE_BUFF };

UENUM(BlueprintType)
enum class TargetType : uint8{ SELF, ENEMY, FRIEND, SELFFRIEND, OWNER };

UENUM(BlueprintType)
enum class Condition : uint8{ BLEEDING, BURNING, DEEPWOUND, POISON, CRIPPLED, DAZED, ALL};

UENUM(BlueprintType)
enum class HBDamageType : uint8{ FIRE, PHYSICAL, WATER, LIGHTNING };

UENUM(BlueprintType)
enum class Trigger : uint8 { DAMAGE, HEAL, HIT, AFTERCAST, CASTMANA, BEFORECAST, NONE};

UENUM(BlueprintType)
enum class ComponentTarget : uint8 { TARGET, SELF };

UENUM(BlueprintType)
enum class CoolDownType : uint8 { CURRENTSKILL, ATTRIBUTE, INTERRUPT, ALL };

UENUM(BlueprintType)
enum class CostType : uint8 {MANA, ADRENALINE, NONE};

UENUM(BlueprintType)
enum class RegnerationType : uint8 { MANA, HEALTH};

UENUM(BlueprintType)
enum class ReductionType : uint8 { PRECENT, VALUE };

UENUM(BlueprintType)
enum class RemoveType : uint8 { HEX, ENTCHANTMENT, STANCE, CONDI };
UENUM()
enum class Weapon : uint8
{
	SWORD, AXE, HAMMER, BOW, STAFF, SPEAR, NONE
};

class HEROBATTLE_API SkillEnums
{
public:
	SkillEnums();
	~SkillEnums();

	
	static Attributes stringToAttribute(FString sAttribute);
	static ProfessionName stringToProfessionName(FString sProfessionName);
	static SkillType stringToSkillType(FString sSkillType);
	static TargetType stringToTargetType(FString sTargetType);
	static Condition stringToCondition(FString sCondition);
	static HBDamageType stringToHBDamageType(FString sHBDamageType);
	static Trigger stringToTrigger(FString sTrigger);
	static ComponentTarget stringToComponentTarget(FString sComponentTarget);
	static CoolDownType stringToCoolDownType(FString sCoolDownType);
	static CostType stringToCostType(FString sCostType);
	static RegnerationType stringToRegnerationType(FString sRegnerationType);
	static ReductionType stringTReductionType(FString sReductionTyp);
	static RemoveType stringToRemoveType(FString sRemoveType);
	static Weapon stringToWeapon(FString sWeapon);

	static FString AttributesToString(Attributes attribute);

};
