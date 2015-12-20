// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "Engine.h"
#include "Skill.h"
#include "Components/BaseSkillComponent.h"
#include "Base/BaseCharacter.h"
#include "UnrealNetwork.h"
#include "SkillMessages.h"
#include "AI/SkillScore.h"



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

bool USkill::isValidTarget(ABaseCharacter* target, ABaseCharacter* self)
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
		self->messages->registerMessage(TEXT("Invalide Target"), MessageType::SKILLERROR);
		return false;
	}
}

float USkill::getScore(ABaseCharacter* caster, FCharacterState charcterState)
{
	if (caster->m_Mana - properties.cost < 0)
		return 0.0f;
	else
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
	float currentMana = caster->m_Mana;
	float maxMana = caster->m_MaxMana;
	int regen = caster->m_ManaRegeneration;

	currentMana += (charcterState.DeltaTime * (regen / 3.0));
	float score = currentMana / maxMana;
	return score;
}

void USkill::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USkill, componentList);
}
