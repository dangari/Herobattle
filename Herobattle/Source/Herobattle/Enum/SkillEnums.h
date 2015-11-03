// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

UENUM(BlueprintType)
enum class Attributes : uint8{ FIRE_MAGIC, HEALING_PRAYERS, PROTECTION_PRAYERS };

UENUM(BlueprintType)
enum class ProfessionName : uint8{ ASSASINE, ELEMENTALIST, MONK, DERWISH, NEKROMANT, PARAGON, WARRIOR, MESMER, RITUALIST };

UENUM(BlueprintType)
enum class SkillType : uint8{ ENTCHANTMENT, ATTACK, HEX, SPELL, HEAL };

UENUM(BlueprintType)
enum class TargetType : uint8{ SELF, ENEMY, FRIEND, SELFFREND };

UENUM(BlueprintType)
enum class Condition : uint8{ BLEEDING, FIRE, DEEPWOUND, POISON };



class HEROBATTLE_API SkillEnums
{
public:
	SkillEnums();
	~SkillEnums();
};
