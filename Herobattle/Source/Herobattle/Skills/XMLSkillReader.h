// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Enum/SkillEnums.h"
#include "Components/BaseSkillComponent.h"

/**
 * 
 */
class USkill;
class FXmlNode;
class USkill;

template<typename T> UBaseSkillComponent * createInstance() { return NewObject<T>(); }
typedef UBaseSkillComponent* (*classFuncPtr)();

class HEROBATTLE_API XMLSkillReader
{
public:
	XMLSkillReader();
	~XMLSkillReader();
	TArray<USkill*> ReadXmlSkillFile(FString path);

	
	// read from <spell> node
	USkill* ReadSkill(FXmlNode* skillRootNode);


	static TMap<FString, classFuncPtr> scObjectNameList;

private:

	TArray<UBaseSkillComponent*> createImpact(FXmlNode* impactNode);
	TArray<USkill*> readeSkillsFromXml(FXmlNode* node);
};
