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

	UPROPERTY(Replicated)
	TArray<USkill*> skillList;

	void PostLogin(APlayerController * NewPlayer) override;

	virtual void BeginPlay() override;

};



