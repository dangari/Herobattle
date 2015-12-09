// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BoolObject.h"
#include "BoolCondition.generated.h"


UCLASS()
class HEROBATTLE_API UBoolCondition : public UBoolObject
{
	GENERATED_BODY()
public:

	
	UBoolCondition();
	~UBoolCondition();

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self) override;

	virtual void init(FXmlNode* node, ComponentTarget target) override;

	FString c;
	int treshold;

};