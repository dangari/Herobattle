// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "Enum/SkillEnums.h"
#include "XmlParser.h"
#include "BuffContainer.generated.h"

/**
*
*/

USTRUCT()
struct FBuffContainer
{
	GENERATED_USTRUCT_BODY()

	int scaleTable[20];
	Attributes scaleAttribute;

	TargetType targetType;

	FString buffName;

	FXmlNode* node;

	void fillScaleTable(FXmlNode* node)
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

};
