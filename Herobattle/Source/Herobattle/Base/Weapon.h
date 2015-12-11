// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Weapon.generated.h"

/**
 * 
 */
UENUM()
enum class Weapons : uint8
{
	SWORD,AXE,HAMMER,BOW,STAFF
};

UENUM()
enum class WeaponType : uint8
{
	MELEE, RANGE
};

USTRUCT()
struct FWeapon
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

	FWeapon()
	{

	}

	FWeapon(Weapons weapon)
	{
		switch (weapon)
		{
		case Weapons::SWORD:
			range = 120.0f;
			attackSpeed = 1.33;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::MELEE;
			break;
		case Weapons::AXE:
			range = 120.0f;
			attackSpeed = 1.33;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::MELEE;
			break;
		case Weapons::HAMMER:
			range = 150.0;
			attackSpeed = 1.75;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::MELEE;
			break;
		case Weapons::BOW:
			range = 1000.0f;
			attackSpeed = 1.75;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::RANGE;
			break;
		case Weapons::STAFF:
			range = 800.0f;
			attackSpeed = 1.75;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			wType = WeaponType::RANGE;
			break;
		default:
			break;
		}
	}
	
};
