// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "Containers/Array.h"
#include "ScWhenCondition.generated.h"


class BoolObject;

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScWhenCondition : public UBaseSkillComponent
{
	GENERATED_BODY()
public:
	UScWhenCondition();
	~UScWhenCondition();
	virtual void run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual float getScore() override;


private:
	TArray<UBaseSkillComponent*> scTable; // components that gets executed when condition is true
	TArray<BoolObject*> boolObjects;

	bool testConditions(ABaseCharacter* target, ABaseCharacter* self);

	virtual void init(FXmlNode* node) override;


};
