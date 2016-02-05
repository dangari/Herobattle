// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BcAdrenaline.h"




UBcAdrenaline::UBcAdrenaline()
{

}

UBcAdrenaline::~UBcAdrenaline()
{

}

bool UBcAdrenaline::run(ABaseCharacter* caster, ABaseCharacter* self, int value /*= 0*/)
{
	ABaseCharacter* newTarget = getTarget(caster, self);
	newTarget->addAdrenaline(m_AdrenalineValue);
	return true;
}

bool UBcAdrenaline::runSim(UAISimCharacter* caster, UAISimCharacter* self, int value /*= 0*/)
{
	UAISimCharacter* newTarget = getTargetSim(caster, self);
	newTarget->addAdrenaline(m_AdrenalineValue);
	return true;
}

float UBcAdrenaline::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	skillScore->addScore(1.f, TEXT("adrenaline"));
	return 1.f;
}

float UBcAdrenaline::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore, float duration)
{
	skillScore->addScore(1.f, TEXT("adrenaline"));
	return 1.f;
}

void UBcAdrenaline::init(FBuffContainer bContainer, ABaseCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::init(bContainer, owner, properties, ownerBuff);
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_AdrenalineValue = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

void UBcAdrenaline::initSim(FBuffContainer bContainer, UAISimCharacter* owner, FSkillProperties properties, UBuff* ownerBuff)
{
	Super::initSim(bContainer, owner, properties, ownerBuff);
	targetType = SkillEnums::stringToTargetType(bContainer.node->GetAttribute(TEXT("target")));
	m_AdrenalineValue = bContainer.scaleTable[owner->getAttributeValue(bContainer.scaleAttribute)];
}

bool UBcAdrenaline::isExpired()
{
	return false;
}

FString UBcAdrenaline::ToString()
{
	return TEXT("Adreanline");
}
