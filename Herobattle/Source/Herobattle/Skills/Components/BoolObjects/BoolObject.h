// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "XmlParser.h"
#include "../../../Enum/SkillEnums.h"

class ABaseCharacter;


class HEROBATTLE_API BoolObject : public UObject
{
public:
	BoolObject();
	~BoolObject();

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self);

	virtual void init(FXmlNode* node, TargetType target);
};
