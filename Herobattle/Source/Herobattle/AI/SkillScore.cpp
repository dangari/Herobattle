// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "SkillScore.h"




void USkillScore::addDamage(float Damage, TargetType target)
{
	FComponentScore cScore;
	cScore.value = Damage;
	cScore.target = target;
	m_DamageList.Add(cScore);
}

void USkillScore::addHeal(float Heal, TargetType target)
{
	FComponentScore cScore;
	cScore.value = Heal;
	cScore.target = target;
	m_HealList.Add(cScore);
}

void USkillScore::addScore(float score, FString componentName)
{
	m_ScoreList.Add(componentName, score);
}

void USkillScore::calcDamageScore(float cHealthSelf, float maxHealthSelf, float cHealthTarget, float maxHealthTarget)
{
	float missingHealthSelf = maxHealthSelf - cHealthSelf;
	float missingHealthTarget = maxHealthTarget - cHealthTarget;
	float completeDamageTarget = 0.f;
	float completeDamageSelf = 0.f;
	for (auto& damage : m_DamageList)
	{
		switch (damage.target)
		{
		case TargetType::SELF:
			completeDamageSelf += damage.value;
			break;
		case TargetType::ENEMY:
			completeDamageTarget += damage.value;
			break;
		default:
			break;
		}
	}
	float selfScore = uFunctionDamage(missingHealthSelf, completeDamageSelf);
	float targetScore = uFunctionDamage(missingHealthTarget, completeDamageTarget);
	float score = (selfScore + targetScore) / 2;
	m_ScoreList.Add(TEXT("Damage"), score);
}

void USkillScore::calcHealScore(float cHealthSelf, float maxHealthSelf, float cHealthTarget, float maxHealthTarget)
{
	float missingHealthSelf = maxHealthSelf - cHealthSelf;
	float missingHealthTarget = maxHealthTarget - cHealthTarget;
	float completeHealTarget = 0.f;
	float completeHealSelf = 0.f;
	for (auto& heal : m_HealList)
	{
		switch (heal.target)
		{
		case TargetType::SELF:
			completeHealSelf += heal.value;
			break;
		case TargetType::FRIEND:
			completeHealTarget += heal.value;
			break;
		default:
			break;
		}
	}
	float selfScore = uFunctionHeal(missingHealthSelf, completeHealSelf);
	float targetScore = uFunctionHeal(missingHealthTarget, completeHealTarget);
	float score = (selfScore + targetScore) / 2;
	m_ScoreList.Add(TEXT("Heal"), score);
}

float USkillScore::calcCompleteScore()
{
	int i = 0;
	float compScore = 0.f;
	for (auto& score : m_ScoreList)
	{
		i++;
		compScore += score.Value;
	}
	compScore = compScore / i;
	return compScore;
}

float USkillScore::uFunctionHeal(float missingHealth, float heal)
{
	float score = (heal + m_healOffset) / missingHealth;
	if (score > 1)
	{
		score = 2 - score;
	}
	if (score < 0)
	{
		return 0.f;
	}
	else
	{
		return score;
	}
}

float USkillScore::uFunctionDamage(float missingHealth, float damage)
{
	float score = (damage - m_damageOffset) / missingHealth;
	if (score > 1)
	{
		score = 2 - score;
	}
	if (score < 0)
	{
		return 0.f;
	}
	else
	{
		return score;
	}
}
