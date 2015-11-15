// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScKnockDown.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScKnockDown : public UBaseSkillComponent
{
	GENERATED_BODY()
	
	UScKnockDown();
	~UScKnockDown();

	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual void init(FXmlNode* node) override;
	virtual float getScore() override;
	
	
};
