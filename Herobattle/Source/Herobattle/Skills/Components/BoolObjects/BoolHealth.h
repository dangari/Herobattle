// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BoolObject.h"
#include "BoolHealth.generated.h"


UCLASS()
class HEROBATTLE_API UBoolHealth : public UBoolObject
{
	GENERATED_BODY()
public:

	
	UBoolHealth();
	~UBoolHealth();

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self) override;

	virtual void init(FXmlNode* node, ComponentTarget target) override;

	FString c;
	int treshold;
};