// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BoolObject.h"

class HEROBATTLE_API BoolHealth : public BoolObject
{
public:
	BoolHealth();
	~BoolHealth();

	const char c = '-';

	int treshold;

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self) override;

	virtual void init(FXmlNode* node) override;
};