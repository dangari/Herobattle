// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "ScDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScDamage : public UBaseSkillComponent
{
	GENERATED_BODY()
public:
	UScDamage();
	~UScDamage();
	virtual void run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual float getScore() override;

	virtual void init(FXmlNode* node) override;

	
private:
	static RegisterComponent<UScDamage> reg1;

};
