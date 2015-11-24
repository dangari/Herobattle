// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "SkillMessages.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class MessageType : uint8 {SKILLERROR,DAMAGE,HEAL};

UCLASS()
class HEROBATTLE_API USkillMessages : public UObject
{
	GENERATED_BODY()

public:
	USkillMessages();
	~USkillMessages();

	UFUNCTION(BlueprintCallable, Category = Message)
	void registerMessage(FString message, MessageType mType);
	
	UFUNCTION(BlueprintCallable, Category = Message)
	bool getNextMessage(FString& out, MessageType mType);
	
	

private:

	bool pop(FString& out, TArray<FString> list);

	UPROPERTY(Replicated)
	TArray<FString> errorList;
	UPROPERTY(Replicated)
	TArray<FString> damageList;
	UPROPERTY(Replicated)
	TArray<FString> healList;

};
