// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "Weapon.h"



FWeaponValues::FWeaponValues()
	: FWeaponValues(Weapon::STAFF)
{
}

FWeaponValues::FWeaponValues(Weapon weapon)
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

int FWeaponValues::getDamage()
{
	return FPlatformMath::RoundToInt(FMath::FRandRange(lowDamage, maxDamage));
}

