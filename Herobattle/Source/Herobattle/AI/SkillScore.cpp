// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "SkillScore.h"




void USkillScore::addDamage(float Damage, ComponentTarget target)
{
	m_damageAdded = true;
	FComponentScore cScore;
	cScore.value = Damage;
	cScore.target = target;
	m_DamageList.Add(cScore);
}

void USkillScore::addHeal(float Heal, ComponentTarget target)
{
	m_healAdded = true;
	FComponentScore cScore;
	cScore.value = Heal;
	cScore.target = target;
	m_HealList.Add(cScore);
}

void USkillScore::addScore(float score, FString componentName)
{
	m_ScoreList.Add(componentName, score);
}

void USkillScore::addDuration(float duration)
{
	m_duration = duration;
}

void USkillScore::calcDamageScore(float cHealthSelf, float maxHealthSelf, float cHealthTarget, float maxHealthTarget)
{
	if(m_damageAdded)
	{
		float missingHealthSelf = maxHealthSelf - cHealthSelf;
		float missingHealthTarget = maxHealthTarget - cHealthTarget;
		float completeDamageTarget = 0.f;
		float completeDamageSelf = 0.f;
		for (auto& damage : m_DamageList)
		{
			switch (damage.target)
			{
			case ComponentTarget::SELF:
				completeDamageSelf += damage.value;
				break;
			case ComponentTarget::TARGET:
				completeDamageTarget += damage.value;
				break;
			default:
				break;
			}
		}
		float selfScore = uFunctionDamage(missingHealthSelf, completeDamageSelf);
		float targetScore = uFunctionDamage(missingHealthTarget, completeDamageTarget);
		float score;
		if (targetScore <= 0.01 || selfScore <= 0.01)
			score = (selfScore + targetScore);
		else
			score = (selfScore + targetScore) / 2;
		m_ScoreList.Add(TEXT("Damage"), score);
	}
}

void USkillScore::calcHealScore(float cHealthSelf, float maxHealthSelf, float cHealthTarget, float maxHealthTarget)
{
	if(m_healAdded)
	{
		float missingHealthSelf = maxHealthSelf - cHealthSelf;
		float missingHealthTarget = maxHealthTarget - cHealthTarget;
		float completeHealTarget = 0.f;
		float completeHealSelf = 0.f;
		if (missingHealthTarget == 0 && missingHealthSelf == 0)
		{
			return;
		}
		for (FComponentScore& heal : m_HealList)
		{
			switch (heal.target)
			{
			case ComponentTarget::SELF:
				completeHealSelf += heal.value;
				break;
			case ComponentTarget::TARGET:
				completeHealTarget += heal.value;
				break;
			default:
				break;
			}
		}
		float selfScore = uFunctionHeal(missingHealthSelf, completeHealSelf);
		float targetScore = uFunctionHeal(missingHealthTarget, completeHealTarget);
		float score;
		if (targetScore <= 0.01 || selfScore <= 0.01)
			score = (selfScore + targetScore);
		else
			score = (selfScore + targetScore) / 2;
		m_ScoreList.Add(TEXT("Heal"), score);
	}
}

void USkillScore::addRegneration(int value)
{
	m_regenChanged = true;
	regen += value;
}

float USkillScore::calcCompleteScore()
{
	if(m_regenChanged)
		clacRegenScore();
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
	if (heal == 0)
		return 0;
	float score = (heal + m_healOffset) / missingHealth;
	if (score > 1)
	{
		score = 2 - score;
	}
	else if (score > 0.5)
	{
		return 1.f;
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
	if (damage == 0)
		return 0;
	float score = (damage * m_damageOffset) / missingHealth;
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

float USkillScore::DurationScore()
{
	if (m_duration <= 0)
	{
		return 1;
	}
	else
	{
		float score = m_duration / m_durationOffset;
		if (score > 2)
		{
			return 2;
		}
		return score;
	}
}

void USkillScore::clacRegenScore()
{
	float score = regen / m_regenOffset;
	if (score > 1)
		score = 1;
	if (score < 0)
		score = 0;

	addScore(score, TEXT("regen"));
}
