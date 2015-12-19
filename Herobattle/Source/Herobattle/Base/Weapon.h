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

	FWeaponValues()
	{

	}

	FWeaponValues(Weapon weapon)
	{
		switch (weapon)
		{
		case Weapon::SWORD:
			range = 120.0f;
			attackSpeed = 1.33;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::MELEE;
			break;
		case Weapon::AXE:
			range = 120.0f;
			attackSpeed = 1.33;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::MELEE;
			break;
		case Weapon::HAMMER:
			range = 150.0;
			attackSpeed = 1.75;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::MELEE;
			break;
		case Weapon::BOW:
			range = 1000.0f;
			attackSpeed = 1.75;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::RANGE;
			break;
		case Weapon::STAFF:
			range = 800.0f;
			attackSpeed = 1.75;
			lowDamage = 11.f;
			maxDamage = 22.f;
			currentTime = attackSpeed;
			wType = WeaponType::RANGE;
			break;
		case Weapon::SPEAR:
			range = 800.0f;
			attackSpeed = 1.5;
			lowDamage = 14.f;
			maxDamage = 27.f;
			currentTime = attackSpeed;
			wType = WeaponType::RANGE;
			break;
		default:
			break;
		}
	}
	
};
