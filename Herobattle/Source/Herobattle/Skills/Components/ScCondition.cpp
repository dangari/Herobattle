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


bool UScCondition::run(ABaseCharacter* target, ABaseCharacter* self)
{
	ABaseCharacter* testTarget;
	if (targetType == TargetType::SELF)
		testTarget = self;
	else
		testTarget = target;
	float duration = scaleTable[self->getAttributeValue(scaleAttribute)];
	UBaseCondition* condition = UBaseCondition::MAKE(conditionType, duration);
	testTarget->applyCondition(condition);
	return true;
	
	
}
float UScCondition::getScore()
{
	return 0.f;
}

void UScCondition::init(FXmlNode* node)
{

	targetType = SkillEnums::stringToTargetType(node->GetAttribute("target"));
	FString cType = node->GetAttribute(TEXT("type"));
	this->conditionType = SkillEnums::stringToCondition(cType);
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("condition")))
	{
		fillScaleTable(node);
	}
}


