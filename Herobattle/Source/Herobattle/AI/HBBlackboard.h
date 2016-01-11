// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Enum/AIEnums.h"
#include "Skills/Skill.h"
#include "HBBlackboard.generated.h"

/**
 * 
 */

UCLASS()
class USimAction : public UObject
{

	GENERATED_BODY()

public:
	UPROPERTY()
	float time;
	UPROPERTY()
	AIAction action;
	UPROPERTY()
	FString targetName;
	UPROPERTY()
	FString ownerName;
	UPROPERTY()
	USkill* skill = nullptr;

	inline static bool ConstPredicate(const USimAction& ip1, const USimAction& ip2)
	{
		return (ip1.time > ip2.time);
	}

};

UCLASS()
class USimCharacter : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TArray<USimAction*> actionList;

};

UCLASS()
class HEROBATTLE_API UHBBlackboard : public UObject
{
	GENERATED_BODY()
public:

	void addAction(FString name, TArray<USimAction*> actionList);


	TArray<USimAction*> getActions(FString name, float DeltaTime);


	TArray<USimAction*> getTargetAction(FString name);


private:

	UPROPERTY()
	TMap<FString, USimCharacter*> actionUserList;

	UPROPERTY()
	TMap<FString, USimCharacter*> actionTargetList;
	
};
