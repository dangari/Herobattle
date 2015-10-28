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