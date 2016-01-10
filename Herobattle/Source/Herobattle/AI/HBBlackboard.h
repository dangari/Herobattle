// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Enum/AIEnums.h"
#include "Skills/Skill.h"
#include "HBBlackboard.generated.h"

/**
 * 
 */

USTRUCT()
struct FSimAction
{

	GENERATED_USTRUCT_BODY()

	float time;
	AIAction action;
	FString targetName;
	FString ownerName;
	USkill* skill;

	inline static bool ConstPredicate(const FSimAction ip1, const FSimAction ip2)
	{
		return (ip1.time > ip2.time);
	}

};

USTRUCT()
struct FSimCharacter
{
	GENERATED_USTRUCT_BODY()

	TArray<FSimAction> actionList;

};

UCLASS()
class HEROBATTLE_API UHBBlackboard : public UObject
{
	GENERATED_BODY()
public:

	void addAction(FString name, TArray<FSimAction> actionList);

	TArray<FSimAction> getActions(FString name, float DeltaTime);

	TArray<FSimAction> getTargetAction(FString name);


private:
	TMap<FString, FSimCharacter> actionUserList;

	TMap<FString, FSimCharacter> actionTargetList;
	
};
