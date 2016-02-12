// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BoolMana.h"
#include "../../../Base/BaseCharacter.h"


UBoolMana::UBoolMana()
{
}

UBoolMana::~UBoolMana()
{
}

bool UBoolMana::test(ABaseCharacter* target, ABaseCharacter* self)
{
	bool test;
	ABaseCharacter* testTarget = getTarget(target, self);

	/*float manaPrec = (testTarget->m_Mana / testTarget->m_MaxMana) * 100;
	if (c.Equals(TEXT("-")))
	{
		test = manaPrec < treshold;
	}
	else
	{
		test = manaPrec > treshold;
	}*/

	if (self->m_Mana > target->m_Mana)
		return true;
	else
		return false;
	return test;
}

bool UBoolMana::testSim(UAISimCharacter* target, UAISimCharacter* self)
{
	bool test;
	UAISimCharacter* testTarget = getTargetSim(target, self);

	/*float manaPrec = (testTarget->m_Mana / testTarget->m_MaxMana) * 100;
	if (c.Equals(TEXT("-")))
	{
	test = manaPrec < treshold;
	}
	else
	{
	test = manaPrec > treshold;
	}*/

	if (self->m_Mana > target->m_Mana)
		return true;
	else
		return false;
	return test;
}

void UBoolMana::init(FXmlNode* node, ComponentTarget target)
{
	targetType = target;
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	
	name = node->GetTag();
	if (name.Equals(TEXT("mana")))
	{
		treshold = FCString::Atoi(*(node->GetAttribute(TEXT("value"))));
		c = node->GetAttribute(TEXT("type"));
	}

}