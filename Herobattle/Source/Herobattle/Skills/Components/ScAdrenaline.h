// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScAdrenaline.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScAdrenaline : public UBaseSkillComponent
{
	GENERATED_BODY()
	ComponentTarget targetType;
	UScAdrenaline();
	~UScAdrenaline();
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName = TEXT("Name")) override;
	virtual bool runSim(UAISimCharacter* target, UAISimCharacter* self, FString SkillName = TEXT("Name")) override;

	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;
	virtual float getScoreSim(UAISimCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FXmlNode* node, FSkillProperties properties) override;

	virtual FString ToString() override;
	
	
	
};
