// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScForEach.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScForEach : public UBaseSkillComponent
{
	GENERATED_BODY()
public:

	UScForEach();
	~UScForEach();

	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual void init(FXmlNode* node) override;
	virtual float getScore() override;
	
private:
	FString skillType;
	TArray<UBaseSkillComponent*> scList;
};
