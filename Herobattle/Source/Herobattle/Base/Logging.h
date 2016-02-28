// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Logging.generated.h"

/**
 * 
 */

class AHeroBattleHero;

USTRUCT()
struct FSimpleArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TArray<float> valueArray;
	UPROPERTY()
	TArray<float> timeStamps;
	UPROPERTY()
	TArray<uint8> slotArray;

	FString valueToString();
	FString timeStampsToString();
	FString slotsToString();

	FString arrayToString(TArray<float> array, FString name);
};

UCLASS()
class HEROBATTLE_API ULogging : public UObject
{
	GENERATED_BODY()
public:

	ULogging();
	~ULogging();

	void addHealth(float value, float timeStamp, FString name);
	void addMana(float value, float timeStamp, FString name);
	void addSkill(int slot, FString name);

	void update(float DeltaTime);

	void printToLog();

	UPROPERTY()
	TMap<FString, FSimpleArray> health;
	UPROPERTY()
	TMap<FString, FSimpleArray> mana;
	UPROPERTY()
	TMap<FString, FSimpleArray> skill;
	UPROPERTY()
	TArray<AHeroBattleHero*> heroes;
	

	float m_completeTime;
	float m_timeStamp;

	bool isPrinted = false;
	bool loggingOn;
};
