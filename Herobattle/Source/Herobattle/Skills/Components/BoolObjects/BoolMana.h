// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BoolObject.h"
#include "BoolMana.generated.h"


UCLASS()
class HEROBATTLE_API UBoolMana : public UBoolObject
{
	GENERATED_BODY()
public:

	
	UBoolMana();
	~UBoolMana();

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual bool testSim(UAISimCharacter* target, UAISimCharacter* self) override;


	virtual void init(FXmlNode* node, ComponentTarget target) override;

	FString c;
	int treshold;
};