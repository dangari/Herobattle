// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "SkillMessages.h"
#include "UnrealNetwork.h"



USkillMessages::USkillMessages()
{
}

USkillMessages::~USkillMessages()
{

}

void USkillMessages::registerMessage(FString message, MessageType mType)
{
	//switch (mType)
	//{
	//case MessageType::SKILLERROR:
	//	errorList.Add(message);
	//	break;
	//case MessageType::DAMAGE:
	//	damageList.Add(message);
	//	break;
	//case MessageType::HEAL:
	//	healList.Add(message);
	//	break;
	//default:
	//	break;
	//}

}

bool USkillMessages::getNextMessage(FString& out,MessageType mType)
{
	switch (mType)
	{
	case MessageType::SKILLERROR:
		return pop(out, errorList);
		break;
	case MessageType::DAMAGE:
		return pop(out, damageList);
		break;
	case MessageType::HEAL:
		return pop(out, healList);
		break;
	default:
		break;
	}
	return true;
	
}



bool USkillMessages::pop(FString& out, TArray<FString> list)
{
	if (errorList.Num() > 0)
	{
		out = errorList[0];
		errorList.RemoveAt(0);
		return true;
	}
	return false;
}



void USkillMessages::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USkillMessages, errorList);
	DOREPLIFETIME(USkillMessages, damageList);
	DOREPLIFETIME(USkillMessages, healList);
}