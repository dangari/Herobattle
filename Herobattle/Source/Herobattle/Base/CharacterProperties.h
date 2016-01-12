// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Enum/CharacterEnums.h"
#include "Enum/SkillEnums.h"
#include "Skills/Skill.h"
#include "Skills/Condition/BaseCondition.h"
#include "CharacterProperties.generated.h"

class ABaseCharacter;
class UBuff;
/**
 * 
 */


USTRUCT(BlueprintType)
struct FAdrenaline
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 currentAdrenaline = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
		int32 maxAdrenaline = 0;
};


USTRUCT(BlueprintType)
struct FSkillCooldown
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	float currentCooldown = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
		float maxCooldown = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
		float additionalCoolDown = 0.f;
};

USTRUCT(BlueprintType)
struct FBuffList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<FString, UBuff*> m_BuffList;
};


USTRUCT()
struct HEROBATTLE_API FCharacterProperties
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	float m_MaxHealth;
	UPROPERTY()
	float m_Health;
	UPROPERTY()
	int32 m_HealthRegeneration;

	UPROPERTY()
	float m_MaxMana;
	UPROPERTY()
	float m_Mana;
	UPROPERTY()
	int32 m_ManaRegeneration;

	UPROPERTY()
	TeamColor ETeam;
	UPROPERTY()
	ProfessionName proffession;

	UPROPERTY()
	TArray<USkill*> skillList;

	UPROPERTY()
	TMap<Condition, UBaseCondition*> m_condtionList;

	UPROPERTY()
	TMap<FString, Trigger> m_BuffList;
	UPROPERTY()
	TMap<Trigger, FBuffList> m_CompleteBuffList;

	UPROPERTY()
	TMap<Attributes, uint8> attrList;

	UPROPERTY()
	FSkillCooldown skillcooldowns[8];

	UPROPERTY()
	FAdrenaline m_AdrenalineList[8];

	UPROPERTY()
	FWeaponValues weapon;

	UPROPERTY()
	HBCharacterState m_State;

	UPROPERTY()
	int32 m_ManaReduction;
	UPROPERTY()
	float m_DamageReduction;
	UPROPERTY()
	int32 m_HealthBuffRegneration;
	UPROPERTY()
	int32  m_ManaBuffRegneration;

	UPROPERTY()
	ABaseCharacter* selectedTarget;

	UPROPERTY()
	FVector location;
};
