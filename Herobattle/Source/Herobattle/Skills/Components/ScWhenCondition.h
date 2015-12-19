// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "Containers/Array.h"
#include "../../Enum/SkillEnums.h"
#include "ScWhenCondition.generated.h"


class UBoolObject;

/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScWhenCondition : public UBaseSkillComponent
{
	GENERATED_BODY()
public:
	UScWhenCondition();
	~UScWhenCondition();
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName = TEXT("Name")) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;

	FString ToString() override;

private:

	UPROPERTY(Replicated)
	TArray<UBaseSkillComponent*> scTable; // components that gets executed when condition is true
	UPROPERTY(Replicated)
	TArray<UBoolObject*> boolObjects;

	bool testConditions(ABaseCharacter* target, ABaseCharacter* self);

	virtual void init(FXmlNode* node, FSkillProperties properties) override;

	void createBoolObjects(FXmlNode* node);
	
	void createSkillComponents(FXmlNode* node, FSkillProperties properties);


};
