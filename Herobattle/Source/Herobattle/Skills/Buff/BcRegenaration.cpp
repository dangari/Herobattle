// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcRegenaration.h"
#include "Base/BaseCharacter.h"
#include "AI/SkillScore.h"
#include "AI/AISimCharacter.h"
#include "Buff.h"



UBcRegenaration::UBcRegenaration()
{

}

UBcRegenaration::~UBcRegenaration()
{

}

bool UBcRegenaration::run(ABaseCharacter* caster, ABaseCharacter* self, int value)
{
	ABaseCharacter* newTarget = getTarget(caster, self);
	newTarget->applyRegneration(m_Regenration, type);
	return true;
}

bool UBcRegenaration::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	UAISimCharacter* newTarget = getTargetSim(caster, self);
	newTarget->applyRegneration(m_Regenration, type);
	return true;
}

float UBcRegenaration::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	skillScore->addRegneration(m_Regenration);
	return 1.f;
}

float UBcRegenaration::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	skillScore->addRegneration(m_Regenration);
	return 1.f;
}

void UBcRegenaration::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::init(bContainer, owner, properties, ownerBuff);
	FString tagName = bContainer.node->GetTag();
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_Regenration = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
	type = SkillEnums::stringToRegnerationType(bContainer.node->GetAttribute(TEXT("type")));
}

void UBcRegenaration::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::initSim(bContainer, owner, properties, ownerBuff);
	FString tagName = bContainer.node->GetTag();
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_Regenration = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
	type = SkillEnums::stringToRegnerationType(bContainer.node->GetAttribute(TEXT("type")));
}

bool UBcRegenaration::isExpired()
{
	return false;
}

FString UBcRegenaration::ToString()
{
	return Super::ToString();
}
