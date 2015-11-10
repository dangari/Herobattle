#include "Herobattle.h"
#include "BaseSkillComponent.h"
#include "XmlParser.h"
#include "Engine.h"
#include "../RegisterSkillComponents.h"
#include "../../Base/BaseCharacter.h"


UBaseSkillComponent::UBaseSkillComponent()
{
	
}


UBaseSkillComponent::~UBaseSkillComponent()
{
}


void UBaseSkillComponent::run(ABaseCharacter* target, ABaseCharacter* self)
{

}
float UBaseSkillComponent::getScore()
{
	return 0.f;
}


void UBaseSkillComponent::init(FXmlNode* node)
{

}

void UBaseSkillComponent::fillScaleTable(FXmlNode* node)
{
	int standartValue = FCString::Atoi(*(node->GetAttribute(TEXT("value"))));
	scaleTable[0] = standartValue;
	scaleAttribute = SkillEnums::stringToAttribute(node->GetAttribute(TEXT("scaling")));
	if (scaleAttribute != Attributes::NONE)
	{
		TArray<FXmlNode*> propertyList = node->GetChildrenNodes();
		//reads the scale table values
		for (auto& prop : propertyList)
		{
			int index = FCString::Atoi(*(prop->GetAttribute(TEXT("key"))));
			int value = FCString::Atoi(*(prop->GetAttribute(TEXT("value"))));
			scaleTable[index] = value;
		}
	}
	// fills the empty spaces off the scaletable array
	for (int Index = 0; Index < 19; ++Index)
	{
		int value1 = scaleTable[Index];
		int value2 = scaleTable[Index + 1];
		if (value2 == 0)
		{
			scaleTable[Index + 1] = value1;
		}
	}
}

UBaseSkillComponent* UBaseSkillComponent::MAKE()
{
	UBaseSkillComponent* w = NewObject<UBaseSkillComponent>();
	return w;
}


