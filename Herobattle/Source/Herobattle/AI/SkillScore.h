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
	TargetType target;
};

/**
 * 
 */
UCLASS()
class HEROBATTLE_API USkillScore : public UObject
{
	GENERATED_BODY()
public:

	void addDamage(float Damage, TargetType target);
	void addHeal(float Heal, TargetType target);
	void addScore(float score, FString componentName);

private:

	TArray<FComponentScore> m_DamageList;
	TArray<FComponentScore> m_HealList;
	TMap<FString, float> m_ScoreList;
	
	
	
};
