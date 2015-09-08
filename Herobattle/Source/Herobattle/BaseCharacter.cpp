// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{
	status = CharacterState::ALIVE;

	health = 480;
	mana = 20;

	healthRegeneration = 0;
	manaRegeneration = 2;


}

BaseCharacter::~BaseCharacter()
{
}
