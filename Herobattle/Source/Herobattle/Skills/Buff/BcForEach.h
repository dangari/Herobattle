// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "BcForEach.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UBcForEach  : public UBaseBuffCompenent
{
	GENERATED_BODY()
public:

	UBcForEach();
	~UBcForEach();

	/*virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual void init(FXmlNode* node) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;
	
private:
	FString skillType;
	TArray<UBaseSkillComponent*> scList;*/
};
