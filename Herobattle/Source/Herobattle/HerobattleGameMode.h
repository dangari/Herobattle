// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
//#include "HeroBattleHero.h"
#include "Skills/Skill.h"
#include "HerobattleGameMode.generated.h"


class AHeroBattleHero;

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

	UPROPERTY(Replicated)
	int32 m_PlayerCount;

	void PostLogin(APlayerController * NewPlayer) override;

	UFUNCTION(BlueprintNativeEvent, Category = "after Login")
	void finishedPostLogin(APlayerController * NewPlayer);
	void finishedPostLogin_Implementation(APlayerController * NewPlayer);
	virtual void BeginPlay() override;

};



