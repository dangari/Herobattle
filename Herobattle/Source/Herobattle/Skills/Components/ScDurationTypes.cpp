#include "Herobattle.h"
#include "ScDurationTypes.h"
#include "../Condition/BaseCondition.h"
#include "../../Base/BaseCharacter.h"


UScCondition::UScCondition()
{
	conditionType = Condition::FIRE;
}


UScCondition::~UScCondition()
{
}


void UScCondition::run(ABaseCharacter* target, ABaseCharacter* self)
{
	float duration = scaleTable[self->getAttributeValue(scaleAttribute)];
	UBaseCondition* condition = UBaseCondition::MAKE(conditionType, duration);
	target->applyCondition(condition);
	
	
}
float UScCondition::getScore()
{
	return 0.f;
}