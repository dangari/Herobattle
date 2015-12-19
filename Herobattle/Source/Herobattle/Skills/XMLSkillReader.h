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

template<typename T> UBaseSkillComponent * createScInstance() { return NewObject<T>(); }
template<typename T> UBaseBuffCompenent * createBcInstance() { return NewObject<T>(); }

typedef UBaseSkillComponent* (*classFuncPtr)();
typedef UBaseBuffCompenent* (*bCclassFuncPtr)();

class HEROBATTLE_API XMLSkillReader
{
public:
	XMLSkillReader();
	~XMLSkillReader();
	TArray<USkill*> ReadXmlSkillFile(FString path);

	
	// read from <spell> node
	USkill* ReadSkill(FXmlNode* skillRootNode);


	static TMap<FString, classFuncPtr> scObjectNameList;
	static TMap<FString, bCclassFuncPtr> bcObjectNameList;

private:

	TArray<UBaseSkillComponent*> createImpact(FXmlNode* impactNode, FSkillProperties properties);
	TArray<USkill*> readeSkillsFromXml(FXmlNode* node);


	FString currentSkillName;
};
