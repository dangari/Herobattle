// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Skills/Components/BaseSkillComponent.h"
#include "../../Enum/SkillEnums.h"
#include "ScBuff.generated.h"


class UBuff;
struct FBuffContainer;



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
	virtual bool run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName = TEXT("Name")) override;
	virtual float getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore) override;
	virtual void init(FXmlNode* node, FSkillProperties properties) override;
	virtual FString ToString() override;

	
	SkillType skillType;

private:

	UBuff* createBuff(float duration);
	
	UPROPERTY()
	TArray<FBuffContainer> bCBuffList;
	bool m_isInfinityUsage;
	FString m_Usage;
	Trigger m_Trigger;
};
