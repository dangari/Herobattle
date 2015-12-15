// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "Herobattle.h"
#include "BaseBuffCompenent.h"

/**
*
*/

void FBuffContainer::fillScaleTable(FXmlNode* node)
{
	scaleTable.Init(0, 20);
	int32 standartValue = FCString::Atoi(*(node->GetAttribute(TEXT("value"))));
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
				int32 index = FCString::Atoi(*(prop->GetAttribute(TEXT("key"))));
				int32 value = FCString::Atoi(*(prop->GetAttribute(TEXT("value"))));
				scaleTable[index] = value;
			}
		}
	}
	// fills the empty spaces off the scaletable array
	for (int32 Index = 0; Index < 19; ++Index)
	{
		int32 value1 = scaleTable[Index];
		int32 value2 = scaleTable[Index + 1];
		if (value2 == 0)
		{
			scaleTable[Index + 1] = value1;
		}
	}
}
	
FString FBuffContainer::ToString()
{
	return buffName;
}
