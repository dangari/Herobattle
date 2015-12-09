// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "XmlParser.h"
#include "../../../Enum/SkillEnums.h"
#include "BoolObject.generated.h"

class ABaseCharacter;

UCLASS()
class HEROBATTLE_API UBoolObject : public UObject
{
	GENERATED_BODY()
public:


	UBoolObject();
	~UBoolObject();

	virtual bool test(ABaseCharacter* target, ABaseCharacter* self);

	virtual void init(FXmlNode* node, ComponentTarget target);


protected:

	ABaseCharacter* getTarget(ABaseCharacter* target, ABaseCharacter* self);

	ComponentTarget targetType;

	FString name;
};
