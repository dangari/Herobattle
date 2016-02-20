// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "Engine.h"
#include "Skill.h"
#include "Components/BaseSkillComponent.h"
#include "Base/BaseCharacter.h"
#include "UnrealNetwork.h"
#include "SkillMessages.h"
#include "AI/SkillScore.h"
#include "AI/AISimCharacter.h"



USkill::USkill()
{
	name = TEXT("default");
}

USkill::~USkill()
{
}

bool USkill::run(ABaseCharacter* target, ABaseCharacter* self)
{
	bool b = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, name);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(properties.cost));
	for (auto& sc : componentList)
	{
		b = sc->run(target, self, name);
	}

	return b;
}

bool USkill::runSim(UAISimCharacter* target, UAISimCharacter* self)
{
	bool b = true;
	for (auto& sc : componentList)
	{
		b = sc->runSim(target, self, name);
	}

	return b;
}

bool USkill::isValidTarget(ABaseCharacter* target, ABaseCharacter* self)
{
	if (target->getState() == HBCharacterState::DEATH)
		return false;
	else if (target->isEnemy(self->ETeam) && properties.targetType == TargetType::ENEMY)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && properties.targetType == TargetType::SELFFRIEND)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && properties.targetType == TargetType::FRIEND && target != self)
	{
		return true;
	}
	else if (target == self && properties.targetType == TargetType::SELF)
	{
		return true;
	}
	else
	{
		self->messages->registerMessage(TEXT("Invalide Target"), MessageType::SKILLERROR);
		return false;
	}
}

bool USkill::isValidTargetSim(UAISimCharacter* target, UAISimCharacter* self)
{
	if (target->isEnemy(self->ETeam) && properties.targetType == TargetType::ENEMY)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && properties.targetType == TargetType::SELFFRIEND)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && properties.targetType == TargetType::FRIEND && target != self)
	{
		return true;
	}
	else if (target == self && properties.targetType == TargetType::SELF)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool USkill::isInRange(ABaseCharacter* target, ABaseCharacter* self)
{
	FVector location = self->GetActorLocation();
	float airDistance = (location - target->GetActorLocation()).Size();
	if (properties.targetType == TargetType::SELF)
	{
		return true;
	}
	else if (properties.range > airDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float USkill::getScore(ABaseCharacter* caster, FCharacterState charcterState)
{

	USkillScore* skillScore = NewObject<USkillScore>();
	for (auto& component : componentList)
	{
		component->getScore(caster, charcterState, skillScore);
	}
	ABaseCharacter* target = charcterState.self;
	skillScore->calcDamageScore(caster->m_Health, caster->m_MaxHealth, target->m_Health, target->m_MaxHealth);
	skillScore->calcHealScore(caster->m_Health, caster->m_MaxHealth, target->m_Health, target->m_MaxHealth);
	float score = skillScore->calcCompleteScore() *  manaScore(caster, charcterState);
	return score;

}

float USkill::getScoreSim(UAISimCharacter* caster, FCharacterState characterState)
{
	
	USkillScore* skillScore = NewObject<USkillScore>();
	
	UAISimCharacter* self = NewObject<UAISimCharacter>(this);
	self->init(characterState);
	characterState.selfSim = self;

	for (auto& component : componentList)
	{
		component->getScoreSim(caster, characterState, skillScore);
	}
	UAISimCharacter* target = characterState.selfSim;
	skillScore->calcDamageScore(caster->m_Health, caster->m_MaxHealth, target->m_Health, target->m_MaxHealth);
	skillScore->calcHealScore(caster->m_Health, caster->m_MaxHealth, target->m_Health, target->m_MaxHealth);
	float score = skillScore->calcCompleteScore() *  manaScoreSim(caster, characterState);
	return score;
}

FString USkill::ToString()
{
	FString skillText = name;
	for (auto& sc : componentList)
	{
		skillText.Append(TEXT("\n"));
		skillText.Append(TEXT("\t"));
		skillText.Append(sc->ToString());
	}
	return skillText;
}

float USkill::manaScore(ABaseCharacter* caster, FCharacterState charcterState)
{
	if (properties.costType == CostType::ADRENALINE || properties.costType == CostType::NONE)
		return 1;
	

	float currentMana = caster->m_Mana;
	float maxMana = caster->m_MaxMana;
	int regen = caster->m_ManaRegeneration;

	int mana_cost = properties.cost - caster->m_ManaReduction;
	if (mana_cost < 0)
		mana_cost = 0;
	float score =  (1 - properties.cost / currentMana) * (regen / 4.0);
	return score;
}

float USkill::manaScoreSim(UAISimCharacter* caster, FCharacterState charcterState)
{
	if (properties.costType == CostType::ADRENALINE && (properties.skillType == SkillType::ATTACK || properties.skillType == SkillType::RANGEATTACK))
		return 1;
	else if (properties.costType == CostType::ADRENALINE)
		return 0.5;
	if (properties.costType == CostType::NONE)
		return 1;
	float currentMana = caster->m_Mana;
	float maxMana = caster->m_MaxMana;
	int regen = caster->m_ManaRegeneration;

	int mana_cost = properties.cost - caster->m_ManaReduction;
	if (mana_cost < 0)
		mana_cost = 0;
	float score = (1 - properties.cost / currentMana) * (regen / 4.0);
	return score;
}

void USkill::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USkill, componentList);
}
