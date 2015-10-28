// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Enum/SkillEnums.h"
#include "BaseCondition.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBaseCondition : public UObject
{
	GENERATED_BODY()
public:
	float duration;
	float currentDuration;
	int regeneration;

	Condition condition;
	UBaseCondition();
	void init(Condition condition, float duration);
	~UBaseCondition();

	static UBaseCondition* MAKE(Condition condition, float duration);
	
};
