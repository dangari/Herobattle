// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScBlock.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScBlock : public UBaseSkillComponent
{
	GENERATED_BODY()
	
	UScBlock();
	~UScBlock();

	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual void init(FXmlNode* node) override;
	virtual float getScore(FCharacterState characterState) override;
	
	int m_usage;
	int m_currentUsage;
};
