// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScCoolDown.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScCoolDown : public UBaseSkillComponent
{
	GENERATED_BODY()

	UScCoolDown();
	~UScCoolDown();

	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FXmlNode* node) override;

	virtual FString ToString() override;
	CoolDownType coolDownType;
	
};
