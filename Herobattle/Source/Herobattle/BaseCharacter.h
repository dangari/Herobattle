// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/Profession.h"
#include "Base/Skill.h"
/**
 * 
 */

enum CharacterState{ALIVE, DEAD};

class HEROBATTLE_API BaseCharacter
{
public:
	BaseCharacter();
	~BaseCharacter();

	int getHealth();
	int getMana();

	void damageCharacter(int damge);
	void changeMana(int mana);

private:

	CharacterState status;

	int health;
	int mana;

	int healthRegeneration;
	int manaRegeneration;

	Profession primaryProfession;
	Profession secondaryProfession;

	Skill skillBuild[];
};
