// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Enum/SkillEnums.h"
#include "SkillScore.generated.h"


USTRUCT()
struct FComponentScore
{

	GENERATED_USTRUCT_BODY()

	float value;
	ComponentTarget target;
};

/**
 * 
 */
UCLASS()
class HEROBATTLE_API USkillScore : public UObject
{
	GENERATED_BODY()
public:

	void addDamage(float Damage, ComponentTarget target);
	void addHeal(float Heal, ComponentTarget target);
	void addScore(float score, FString componentName);
	void addDuration(float duration);

	void calcDamageScore(float cHealthSelf, float maxHealthSelf, float cHealthTarget, float maxHealthTarget);
	void calcHealScore(float cHealthSelf, float maxHealthSelf, float cHealthTarget, float maxHealthTarget);

	float DurationScore();

	void addRegneration(int value);

	float calcCompleteScore();


private:

	TArray<FComponentScore> m_DamageList;
	TArray<FComponentScore> m_HealList;
	TMap<FString, float> m_ScoreList;
	
	float uFunctionHeal(float missingHealth, float heal);
	float uFunctionDamage(float missingHealth, float damage);
	void clacRegenScore();

	int regen = 0;
	float m_healOffset = 30.f;
	float m_damageOffset = 0.9;
	float m_regenOffset = 7;
	float m_duration = 0;
	float m_durationOffset = 5;
	bool m_regenChanged = false;
	bool m_damageAdded = false;
	bool m_healAdded = false;
};
