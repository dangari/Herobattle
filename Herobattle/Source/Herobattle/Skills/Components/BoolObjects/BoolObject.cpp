// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolObject.h"
#include "../../../Base/BaseCharacter.h"

BoolObject::BoolObject()
{
}

BoolObject::~BoolObject()
{
}

bool BoolObject::test(ABaseCharacter* target, ABaseCharacter* self)
{
	return true;
}


BoolHealth::BoolHealth()
{
}

BoolHealth::~BoolHealth()
{
}

bool BoolHealth::test(ABaseCharacter* target, ABaseCharacter* self)
{
	bool test;
	float healthPrec = (target->m_MaxHealth / target->m_MaxHealth) * 100;
	if (c == '-')
	{
		test = healthPrec < treshold;
	}
	else
	{
		test = healthPrec > treshold;
	}
	return test;
}