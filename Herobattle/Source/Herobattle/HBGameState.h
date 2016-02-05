// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Skills/Skill.h"
#include "HBGameState.generated.h"

/**
 * 
 */

class ULogging;

USTRUCT(BlueprintType)
struct FDebugSkill
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Info)
	FString name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Info)
	FString descrition;
};

UCLASS()
class HEROBATTLE_API AHBGameState : public AGameState
{
	GENERATED_BODY()
public:

	AHBGameState();
	~AHBGameState();

	virtual void BeginPlay() override;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = Info)
	TArray<FDebugSkill> DebugSkillList;
	
	UPROPERTY()
	ULogging* logging;

};
