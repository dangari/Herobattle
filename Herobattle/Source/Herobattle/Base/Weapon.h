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

USTRUCT()
struct FWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY();
	float range;
	UPROPERTY();
	float attackSpeed;
	UPROPERTY();
	float currentTime;
	UPROPERTY();
	int lowDamage;
	UPROPERTY();
	int maxDamage;
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
			break;
		case Weapons::AXE:
			range = 120.0f;
			attackSpeed = 1.33;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			break;
		case Weapons::HAMMER:
			range = 150.0;
			attackSpeed = 1.75;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			break;
		case Weapons::BOW:
			range = 1000.0f;
			attackSpeed = 1.75;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			break;
		case Weapons::STAFF:
			range = 800.0f;
			attackSpeed = 1.75;
			lowDamage = 24.0f;
			maxDamage = 30.0f;
			currentTime = attackSpeed;
			break;
		default:
			break;
		}
	}
	
};
