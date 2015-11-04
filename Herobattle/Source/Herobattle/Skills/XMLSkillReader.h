// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Enum/SkillEnums.h"
#include "Components/BaseSkillComponent.h"

/**
 * 
 */
class USkill;
class FXmlNode;

//template<typename T> UBaseSkillComponent * createInstance() 
//{ 
//	return NewObject<T>();
//}

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
	UBaseSkillComponent* createImpact(FXmlNode* impactNode);
	TMap<FString, UBaseSkillComponent*(*)> scObjectNameList;
};
