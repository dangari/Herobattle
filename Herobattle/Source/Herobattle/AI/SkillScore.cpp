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
