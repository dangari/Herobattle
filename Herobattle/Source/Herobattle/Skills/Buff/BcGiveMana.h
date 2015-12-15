// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScGiveMana.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScGiveMana : public UBaseSkillComponent
{
	GENERATED_BODY()

public:

	UScGiveMana();
	~UScGiveMana();
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FXmlNode* node) override;

	virtual FString ToString() override;
	
private:
	int treshhold = -10;
	
};
