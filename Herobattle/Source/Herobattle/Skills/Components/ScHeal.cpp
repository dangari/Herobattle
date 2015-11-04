#include "Herobattle.h"
#include "ScHeal.h"
#include "../../Base/BaseCharacter.h"

UScHeal::UScHeal()
{
}


UScHeal::~UScHeal()
{
}


void UScHeal::run(ABaseCharacter* target, ABaseCharacter* self)
{
	Super::run(target, self);
	float heal = scaleTable[self->getAttributeValue(scaleAttribute)];
	target->heal(heal);
}
float UScHeal::getScore()
{
	return 1.f;
}

void UScHeal::init(FXmlNode* node)
{
//	throw std::logic_error("The method or operation is not implemented.");
}
