// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ABaseCharacter;
/**
 * 
 */
class HEROBATTLE_API BoolObject
{
public:
	BoolObject();
	~BoolObject();

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self);
};


class HEROBATTLE_API BoolHealth : BoolObject
{
public:
	BoolHealth();
	~BoolHealth();

	const char c = '-';

	int treshold;

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self) override;
};