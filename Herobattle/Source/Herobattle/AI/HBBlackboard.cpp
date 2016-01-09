// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "HBBlackboard.h"




void UHBBlackboard::addAction(FString name, TArray<FSimAction> actionList)
{
	if (actionUserList.Contains(name))
	{
		FSimCharacter character = *actionUserList.Find(name);
		character.actionList = actionList;
	}
	else
	{
		FSimCharacter character;
		character.actionList = actionList;
		actionUserList.Add(name, character);
	}
}

TArray<FSimAction> UHBBlackboard::getActions(FString name)
{
	if (actionUserList.Contains(name))
	{
		FSimCharacter character = *actionUserList.Find(name);
		return character.actionList;
	}
	else
	{
		TArray<FSimAction> emptyList;
		return emptyList;
	}
}

TArray<FSimAction> UHBBlackboard::getTargetAction(FString name)
{
	TArray<FSimAction> targetActionList;
	for (auto& character : actionUserList)
	{
		TArray<FSimAction> list = character.Value.actionList;
		for (auto& action : list)
		{
			if (action.targetName.Equals(name) || action.ownerName.Equals(name))
			{
				targetActionList.Add(action);
			}
		}
	}
	targetActionList.Sort(FSimAction::ConstPredicate);
	return targetActionList;
}
