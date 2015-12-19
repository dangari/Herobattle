// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Enum/SkillEnums.h"
#include "Weapon.generated.h"

/**
 * 
 */


UENUM()
enum class WeaponType : uint8
{
	MELEE, RANGE
};

USTRUCT()
struct FWeaponValues
{
	GENERATED_USTRUCT_BODY()

	FWeaponValues();
	FWeaponValues(Weapon weapon);

	UPROPERTY()
	float range;
	UPROPERTY()
	float attackSpeed;
	UPROPERTY()
	float currentTime;
	UPROPERTY()
	int32 lowDamage;
	UPROPERTY()
	int32 maxDamage;

	UPROPERTY()
	WeaponType wType;
	
	int getDamage();
};
