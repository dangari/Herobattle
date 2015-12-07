// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScRegeneratio.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScRegeneratio : public UBaseSkillComponent
{
	GENERATED_BODY()

	UScRegeneratio();
	~UScRegeneratio();
	
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual void init(FXmlNode* node) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;
	
};
