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

	void fillScaleTable(FXmlNode* node);

	FString ToString();

};
