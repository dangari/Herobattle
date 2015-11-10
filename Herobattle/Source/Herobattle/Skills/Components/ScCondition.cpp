#include "Herobattle.h"
#include "ScCondition.h"
#include "../Condition/BaseCondition.h"
#include "../../Base/BaseCharacter.h"
#include "../RegisterSkillComponents.h"


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

void UScCondition::init(FXmlNode* node)
{
//	throw std::logic_error("The method or operation is not implemented.");
}

RegisterComponent<UScCondition> UScCondition::reg1(TEXT("test1"));
//template<typename T>
//TMap<FString, classFuncPtr>  RegisterComponent<T>::map;

