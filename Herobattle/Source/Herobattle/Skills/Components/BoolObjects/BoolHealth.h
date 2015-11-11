// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BoolObject.h"

class HEROBATTLE_API BoolHealth : public BoolObject
{
public:
	BoolHealth();
	~BoolHealth();

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self) override;

	virtual void init(FXmlNode* node, TargetType target) override;

	FString c;
	int treshold;

	TargetType targetType;
};