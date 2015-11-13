#include "Herobattle.h"
#include "ScCondition.h"
#include "../Condition/BaseCondition.h"
#include "../../Base/BaseCharacter.h"
#include "../RegisterSkillComponents.h"
#include "../../Enum/SkillEnums.h"

UScCondition::UScCondition()
{
	conditionType = Condition::BURNING;
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

void UScCondition::init(FXmlNode* node)
{
	FString cType = node->GetAttribute(TEXT("type"));
	this->conditionType = SkillEnums::stringToCondition(cType);
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("duration")))
	{
		fillScaleTable(node);
	}
}


