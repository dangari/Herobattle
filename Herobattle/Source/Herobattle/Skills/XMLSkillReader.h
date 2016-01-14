// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Enum/SkillEnums.h"

/**
 * 
 */
class USkill;
class FXmlNode;
class USkill;
class UBaseSkillComponent;
class UBaseBuffCompenent;

template<typename T> UBaseSkillComponent * createScInstance(UObject* obj) { return NewObject<T>(obj); }

typedef UBaseSkillComponent* (*classFuncPtr)(UObject* obj);

class HEROBATTLE_API XMLSkillReader
{
public:
	XMLSkillReader();
	~XMLSkillReader();
	TArray<USkill*> ReadXmlSkillFile(FString path, UObject* owner);

	
	// read from <spell> node
	USkill* ReadSkill(FXmlNode* skillRootNode, UObject* owner);


	static TMap<FString, classFuncPtr> scObjectNameList;

private:

	TArray<UBaseSkillComponent*> createImpact(FXmlNode* impactNode, FSkillProperties properties, UObject* owner);
	TArray<USkill*> readeSkillsFromXml(FXmlNode* node, UObject* owner);


	FString currentSkillName;
};
