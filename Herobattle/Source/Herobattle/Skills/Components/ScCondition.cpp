#include "Herobattle.h"
#include "ScCondition.h"
#include "../Condition/BaseCondition.h"
#include "../RegisterSkillComponents.h"
#include "../../Enum/SkillEnums.h"
#include "Base/BaseCharacter.h"
#include "AI/AISimCharacter.h"
#include "AI/SkillScore.h"

UScCondition::UScCondition()
{
	componentName = TEXT("Condition");
}


UScCondition::~UScCondition()
{
}


bool UScCondition::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	ABaseCharacter* testTarget =getTarget(target,self);
	float duration = scaleTable[self->getAttributeValue(scaleAttribute)];
	UBaseCondition* condition = UBaseCondition::MAKE(conditionType, duration);
	testTarget->applyCondition(condition);
	return true;
	
	
}

bool UScCondition::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	UAISimCharacter* testTarget = getTargetSim(target, self);
	float duration = scaleTable[self->getAttributeValue(scaleAttribute)];
	UBaseCondition* condition = UBaseCondition::MAKE(conditionType, duration);
	testTarget->applyCondition(condition);
	return true;
}

float UScCondition::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	skillScore->addScore(1.f, componentName);
	return 0.f;
}

float UScCondition::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	skillScore->addScore(1.f, componentName);
	return 0.f;
}

void UScCondition::init(FXmlNode* node, FSkillProperties properties)
{
	Super::init(node, properties);
	targetType = SkillEnums::stringToTargetType(node->GetAttribute("target"));
	FString cType = node->GetAttribute(TEXT("type"));
	this->conditionType = SkillEnums::stringToCondition(cType);
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("condition")))
	{
		fillScaleTable(node);
	}
}

FString UScCondition::ToString()
{
	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());

	return sCText;
}

