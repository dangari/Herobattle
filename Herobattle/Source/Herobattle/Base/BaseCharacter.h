// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/Profession.h"
/**
 * 
 */
class HEROBATTLE_API BaseCharacter
{
public:
	BaseCharacter();
	~BaseCharacter();

private:

	int health;
	int mana;

	int manaRegeneration;

	Profession primaryProfession;
	Profession secondaryProfession;


};
