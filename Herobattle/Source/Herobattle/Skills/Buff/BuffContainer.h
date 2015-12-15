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

	TArray<int32> scaleTable;
	Attributes scaleAttribute;

	TargetType targetType;

	FString buffName;

	FXmlNode* node;

	void fillScaleTable(FXmlNode* node);

	FString ToString();

};
