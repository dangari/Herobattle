// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
//#include "HeroBattleHero.h"
#include "Skills/Skill.h"
#include "HerobattleGameMode.generated.h"


class AHeroBattleHero;
class ULogging;
class ABaseCharacter;

USTRUCT()
struct FDeathCharacter
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float leftTime;

	UPROPERTY()
	ABaseCharacter* character;
};

UCLASS(minimalapi)
class AHerobattleGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AHerobattleGameMode();

	// Hereos of the Blue Team
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TeamBlue)
	AHeroBattleHero* blueHero_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TeamBlue)
	AHeroBattleHero* blueHero_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TeamBlue)
	AHeroBattleHero* blueHero_3;

	// Hereos of the Blue Team
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TeamRed)
	AHeroBattleHero* redHero_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TeamRed)
	AHeroBattleHero* redHero_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TeamRed)
	AHeroBattleHero* redHero_3;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = TeamRed)
	TArray<USkill*> skillList;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = General)
	float RespawnTime = 30.f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = General)
	float CapturePointSpeed = 107.0f;

	UPROPERTY(Replicated)
	int32 m_PlayerCount;
	ULogging* logging;
	void PostLogin(APlayerController * NewPlayer) override;

	UFUNCTION(BlueprintNativeEvent, Category = afterLogin)
	void finishedPostLogin(APlayerController * NewPlayer);
	void finishedPostLogin_Implementation(APlayerController * NewPlayer);

	UFUNCTION(BlueprintNativeEvent, Category = Respawn)
	void moveToSpawnLocation(ABaseCharacter* character);

	void moveToSpawnLocation_Implementation(ABaseCharacter* character);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//get called when a shrine gets captured
	void addShrine(uint8 pips, TeamColor team);

	//get called when a shrine gets decapped
	void removeShrine(uint8 pips, TeamColor team);
	
	void UpdateScore(float DeltaSeconds);

	void addDeathCharacter(ABaseCharacter* character);

private:

	UPROPERTY()
	uint8 m_BluePips;
	UPROPERTY()
	uint8 m_RedPips;

	UPROPERTY()
	TMap<FString, FDeathCharacter> deathList;

	void updateDeathList(float DeltaSeconds);
};



