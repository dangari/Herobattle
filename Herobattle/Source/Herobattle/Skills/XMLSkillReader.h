// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Enum/SkillEnums.h"

/**
 * 
 */
class USkill;
class FXmlNode;

class HEROBATTLE_API XMLSkillReader
{
public:
	XMLSkillReader();
	~XMLSkillReader();
	USkill* ReadXmlSkillFile(FString path);

	
	// read from <spell> node
	USkill* ReadSkill(FXmlNode* skillRootNode);

private:

	TargetType getTargetTypeFromString(FString name);
};
