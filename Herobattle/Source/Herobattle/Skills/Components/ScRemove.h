// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScRemove.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScRemove : public UBaseSkillComponent
{
	GENERATED_BODY()
	
public:
	UScRemove();
	~UScRemove();
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName = TEXT("Name")) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	virtual void init(FXmlNode* node, FSkillProperties properties) override;

	virtual FString ToString() override;

private:

	RemoveType rType;
	
};
