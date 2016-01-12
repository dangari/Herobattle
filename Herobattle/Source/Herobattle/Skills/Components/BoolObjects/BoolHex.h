// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BoolObjects/BoolObject.h"
#include "BoolHex.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBoolHex : public UBoolObject
{
	GENERATED_BODY()
	
public:


	UBoolHex();
	~UBoolHex();

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual bool testSim(UAISimCharacter* target, UAISimCharacter* self) override;


	virtual void init(FXmlNode* node, ComponentTarget target) override;

	FString c;
	int treshold;
	
	
};
