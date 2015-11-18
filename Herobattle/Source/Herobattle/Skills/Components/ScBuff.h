// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "../../Enum/SkillEnums.h"
#include "ScBuff.generated.h"


class UBaseBuff;

typedef UBaseSkillComponent* (*classFuncPtr)();
/**
 * 
 */
UCLASS()
class HEROBATTLE_API UScBuff : public UBaseSkillComponent
{
	GENERATED_BODY()
public:
	UScBuff();
	~UScBuff();
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self) override;
	virtual float getScore() override;
	virtual void init(FXmlNode* node) override;
	virtual FString ToString() override;

	
	SkillType skillType;

private:

	UBaseBuff* createBuff(float duration);

	TArray<classFuncPtr> sCBuffList;
	bool m_isInfinityUsage;
	FString m_Usage;
};
