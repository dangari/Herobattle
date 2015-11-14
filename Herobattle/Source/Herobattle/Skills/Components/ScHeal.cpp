#include "Herobattle.h"
#include "ScHeal.h"
#include "../../Base/BaseCharacter.h"

UScHeal::UScHeal()
{
}


UScHeal::~UScHeal()
{
}


bool UScHeal::run(ABaseCharacter* target, ABaseCharacter* self)
{
	Super::run(target, self);
	float heal = scaleTable[self->getAttributeValue(scaleAttribute)];
	target->heal(heal);
	return true;
}
float UScHeal::getScore()
{
	return 1.f;
}

void UScHeal::init(FXmlNode* node)
{
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("heal")))
	{
		fillScaleTable(node);
	}
}
