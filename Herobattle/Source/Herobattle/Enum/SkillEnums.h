// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

UENUM(BlueprintType)
enum class Attributes : uint8{NONE, FIRE_MAGIC, HEALING_PRAYERS, PROTECTION_PRAYERS, STRENGTH };

UENUM(BlueprintType)
enum class ProfessionName : uint8{NONE, ASSASINE, ELEMENTALIST, MONK, DERWISH, NEKROMANT, PARAGON, WARRIOR, MESMER, RITUALIST };

UENUM(BlueprintType)
enum class SkillType : uint8{ATTACK, ENTCHANTMENT, RANGEATTACK,MELEEATTACK , HEX, SPELL, HEAL, UNIQUE_BUFF };

UENUM(BlueprintType)
enum class TargetType : uint8{ SELF, ENEMY, FRIEND, SELFFRIEND, OWNER };

UENUM(BlueprintType)
enum class Condition : uint8{ BLEEDING, BURNING, DEEPWOUND, POISON, CRIPPLED, ALL};

UENUM(BlueprintType)
enum class HBDamageType : uint8{ FIRE, PHYSICAL, WATER, LIGHTNING };

UENUM(BlueprintType)
enum class Trigger : uint8 { DAMAGE, HEAL };

UENUM(BlueprintType)
enum class ComponentTarget : uint8 { TARGET, SELF };

UENUM(BlueprintType)
enum class CoolDownType : uint8 { CURRENTSKILL, ATTRIBUTE, INTERRUPT, ALL };

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

	static FString AttributesToString(Attributes attribute);

};
