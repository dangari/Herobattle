#include "Herobattle.h"
#include "BaseSkillComponent.h"
#include "XmlParser.h"
#include "Engine.h"
#include "../RegisterSkillComponents.h"
#include "../../Base/BaseCharacter.h"
#include "AI/SkillScore.h"
#include "AI/AISimCharacter.h"


UBaseSkillComponent::UBaseSkillComponent()
{

}


UBaseSkillComponent::~UBaseSkillComponent()
{
}


bool UBaseSkillComponent::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	return true;
}

bool UBaseSkillComponent::runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	return true;
}

float UBaseSkillComponent::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	return 0.f;
}


float UBaseSkillComponent::getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	return 1.f;
}

void UBaseSkillComponent::init(FXmlNode* node, FSkillProperties properties)
{
	m_properties = properties;
}

FString UBaseSkillComponent::ToString()
{
	FString sCText = SkillEnums::AttributesToString(scaleAttribute).Append(TEXT(": "));
	for (int i = 0; i<20; i++)
	{
		sCText.Append(TEXT("["));
		sCText.Append(FString::FromInt(scaleTable[i]));
		sCText.Append(TEXT("]"));
	}
	return sCText;
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
			FString tagName = prop->GetTag();
			if (tagName.Equals(TEXT("step")))
			{
				int index = FCString::Atoi(*(prop->GetAttribute(TEXT("key"))));
				int value = FCString::Atoi(*(prop->GetAttribute(TEXT("value"))));
				scaleTable[index] = value;
			}
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

ABaseCharacter* UBaseSkillComponent::getTarget(ABaseCharacter* target, ABaseCharacter* self)
{
	if (targetType == ComponentTarget::SELF)
	{
		return self;
	}
	else
	{
		return target;
	}
}

UAISimCharacter* UBaseSkillComponent::getTargetSim(UAISimCharacter* target, UAISimCharacter* self)
{
	if (targetType == ComponentTarget::SELF)
	{
		return self;
	}
	else
	{
		return target;
	}
}

void UBaseSkillComponent::DestroyObject(UObject* obj)
{
	if (!obj) return;
	if (!obj->IsValidLowLevel()) return;

	obj->ConditionalBeginDestroy(); //instantly clears UObject out of memory
	obj = nullptr;
}

UBaseSkillComponent* UBaseSkillComponent::MAKE()
{
	UBaseSkillComponent* w = NewObject<UBaseSkillComponent>();
	return w;
}


