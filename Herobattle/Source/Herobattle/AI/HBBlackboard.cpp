// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HBBlackboard.h"




void UHBBlackboard::addAction(FString name, TArray<USimAction*> actionList)
{
	if (actionUserList.Num() == 0)
	{
		USimCharacter* character = NewObject<USimCharacter>();
		character->actionList = actionList;
		actionUserList.Add(name, character);
	}
	if (actionUserList.Contains(name))
	{
		USimCharacter* character = *actionUserList.Find(name);
		character->actionList = actionList;
	}
	else
	{
		USimCharacter* character = NewObject<USimCharacter>();
		character->actionList = actionList;
		actionUserList.Add(name, character);
	}
}

TArray<USimAction*> UHBBlackboard::getActions(FString name, float DeltaTime)
{
	if (actionUserList.Contains(name))
	{
		USimCharacter* character = *actionUserList.Find(name);
		return character->actionList;
	}
	else
	{
		TArray<USimAction*> emptyList;
		return emptyList;
	}
}

TArray<USimAction*> UHBBlackboard::getTargetAction(FString name, float StartTime, float duration)
{
	TArray<USimAction*> targetActionList;
	for (auto& character : actionUserList)
	{
		TArray<USimAction*> list = character.Value->actionList;
		for (auto& action : list)
		{
			if (action->targetName.Equals(name) || action->ownerName.Equals(name))
			{
				float futureTime = StartTime + duration;
				if (action->time > StartTime && action->time < futureTime)
				{
					targetActionList.Add(action);
				}
				
			}
		}
	}
	targetActionList.Sort(USimAction::ConstPredicate);
	return targetActionList;
}
