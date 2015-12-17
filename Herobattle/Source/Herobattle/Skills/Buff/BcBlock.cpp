// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcBlock.h"
#include "Enum/CharacterEnums.h"
#include "Base/Weapon.h"




UBcBlock::UBcBlock()
{

}

UBcBlock::~UBcBlock()
{

}

void UBcBlock::init(FBuffContainer bContainer, ABaseCharacter* owner)
{
	FXmlNode* node = bContainer.node;
	blockType = SkillEnums::stringToSkillType(node->GetAttribute(TEXT("type")));
	FString sUsage = node->GetAttribute(TEXT("usage"));
	if (sUsage.Equals(TEXT("INF")))
	{
		haveUsages = false;
	}
	else
	{
		haveUsages = true;
		usage = FCString::Atoi(*sUsage);
	}
	blockChance = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

bool UBcBlock::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	bool b = false;
	switch (blockType)
	{
	case SkillType::ATTACK:
		if (caster->getState() == HBCharacterState::AUTOATTACK)
			b = true;
		else
			b = false;
		break;
	case SkillType::SPELL:
		if (caster->getState() == HBCharacterState::CASTING)
			return true;
		else
			return false;
		break;
	case SkillType::MELEEATTACK:
		if (caster->getState() == HBCharacterState::CASTING && caster->getCurrentSkillType() == SkillType::MELEEATTACK ||
			caster->getState() == HBCharacterState::AUTOATTACK && caster->getWeapon().wType == WeaponType::MELEE)
			b = true;
		else
			b = false;
		break;
	case SkillType::RANGEATTACK:
		if (caster->getState() == HBCharacterState::CASTING && caster->getCurrentSkillType() == SkillType::RANGEATTACK ||
			caster->getState() == HBCharacterState::AUTOATTACK && caster->getWeapon().wType == WeaponType::RANGE)
			b = true;
		else
			b = false;
		break;
	default:
		return false;
		break;
	}
	if (b)
	{
		int blockRand = FPlatformMath::RoundToInt(FMath::FRandRange(0,100));
		if (blockChance <= blockRand)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool UBcBlock::isExpired()
{
	if (haveUsages)
	{
		if (usage > 0)
			return true;
	}
	return false;
}

void UBcBlock::update(float deltaTime)
{

}

float UBcBlock::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	//if (characterState.selectedTarget == caster)
	return 1.f;
}
