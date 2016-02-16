// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
//#include "HeroBattleHero.h"
#include "Skills/Skill.h"
#include "HerobattleGameMode.generated.h"


class AHeroBattleHero;
class ULogging;

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


	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Scores)
	float BlueScore;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Scores)
	float RedScore;


	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General")
	uint8 CapturePointSpeed = 107;

	UPROPERTY(Replicated)
	int32 m_PlayerCount;
	ULogging* logging;
	void PostLogin(APlayerController * NewPlayer) override;

	UFUNCTION(BlueprintNativeEvent, Category = "after Login")
	void finishedPostLogin(APlayerController * NewPlayer);
	void finishedPostLogin_Implementation(APlayerController * NewPlayer);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//get called when a shrine gets captured
	void addShrine(uint8 pips, TeamColor team);

	//get called when a shrine gets decapped
	void removeShrine(uint8 pips, TeamColor team);
	void UpdateScore(float DeltaSeconds);
private:

	UPROPERTY()
	uint8 m_BluePips;
	UPROPERTY()
	uint8 m_RedPips;
};



