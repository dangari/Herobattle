// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseCondition.h"


UBaseCondition::UBaseCondition()
{
	init(Condition::FIRE, 0.f);
}
void UBaseCondition::init(Condition condition, float duration)
{
	this->condition = condition;
	this->duration = duration;
	switch (condition)
	{
	case Condition::BLEEDING :
		regeneration = -3;
		break;
	case Condition::POISON :
		regeneration = -4;
		break;
	case Condition::FIRE:
		regeneration = -7;
		break;
	default:
		regeneration = 0;
		break;
	}
}	

UBaseCondition::~UBaseCondition()
{

}

UBaseCondition* UBaseCondition::MAKE(Condition condition, float duration)
{
	UBaseCondition* w = NewObject<UBaseCondition>();
	w->init(condition, duration);
	return w;
}
