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
	TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
	for (auto& prop : propertyList)
	{
		FString tagName = prop->GetTag();
		if (tagName.Equals(TEXT("heal")))
		{
			fillScaleTable(prop);
		}
	}
}
