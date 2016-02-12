// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcBlock.h"
#include "Enum/CharacterEnums.h"
#include "Base/Weapon.h"
#include "Engine.h"
#include "Base/BaseCharacter.h"
#include "AI/SkillScore.h"
#include "AI/AISimCharacter.h"
#include "Buff.h"




UBcBlock::UBcBlock()
{

}

UBcBlock::~UBcBlock()
{

}

void UBcBlock::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::init(bContainer, owner, properties, ownerBuff);
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

void UBcBlock::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::initSim(bContainer, owner, properties, ownerBuff);
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
		if (caster->getState() == HBCharacterState::AUTOATTACK ||
			caster->getState() == HBCharacterState::CASTING && caster->getCurrentSkillType() == SkillType::MELEEATTACK||
			caster->getState() == HBCharacterState::CASTING && caster->getCurrentSkillType() == SkillType::RANGEATTACK)
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
		float rng = FMath::FRandRange(0.f, 100.f);
		FString TheFloatStr = FString::SanitizeFloat(rng);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TheFloatStr);
		int blockRand = FPlatformMath::RoundToInt(rng);
		if (blockChance <= blockRand)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Blocked"));
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool UBcBlock::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	bool b = false;
	switch (blockType)
	{
	case SkillType::ATTACK:
		if (caster->getState() == HBCharacterState::AUTOATTACK ||
			caster->getState() == HBCharacterState::CASTING && caster->getCurrentSkillType() == SkillType::MELEEATTACK ||
			caster->getState() == HBCharacterState::CASTING && caster->getCurrentSkillType() == SkillType::RANGEATTACK)
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
		float rng = FMath::FRandRange(0.f, 100.f);
		FString TheFloatStr = FString::SanitizeFloat(rng);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TheFloatStr);
		int blockRand = FPlatformMath::RoundToInt(rng);
		if (blockChance <= blockRand)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Blocked"));
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
	if (blockType == SkillType::ATTACK && characterState.attackers > 0)
	{
		skillScore->addScore(1.f, TEXT("block"));
	}
	else if (characterState.caster > 0)
	{
		skillScore->addScore(1.f, TEXT("block"));
	}
	else
	{
		skillScore->addScore(0.f, TEXT("block"));
	}
		
	return 1.f;
}

float UBcBlock::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	if (blockType == SkillType::ATTACK && characterState.attackers > 0)
	{
		skillScore->addScore(1.f, TEXT("block"));
	}
	else if (characterState.caster > 0)
	{
		skillScore->addScore(1.f, TEXT("block"));
	}
	else
	{
		skillScore->addScore(0.f, TEXT("block"));
	}

	return 1.f;
}
