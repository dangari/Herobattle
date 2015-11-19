// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/Profession.h"
#include "../Enum/SkillEnums.h"
#include "../Skills/Components/BaseSkillComponent.h"
#include "Skills/Skill.h"
#include "BaseCharacter.generated.h"


/**
 * 
 */

class UBuff;
class UBaseCondition;




UCLASS()
class HEROBATTLE_API ABaseCharacter: public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	~ABaseCharacter();
	

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float m_MaxHealth;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float m_MaxMana;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float m_Health;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float m_Mana;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 m_ManaRegeneration;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 m_HealthRegeneration;

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Mechanics)
	bool UseSkill(ABaseCharacter* Target, int32 SkillSlot);

	UFUNCTION(BlueprintCallable, Category = Meachnics)
	void ChangeHealth(float value);

	UFUNCTION(BlueprintCallable, Category = Meachnics)
	void ChangeMana(float value);



// this Functions get called by Skills
	void heal(ABaseCharacter* caster, float value);

	void damage(ABaseCharacter* caster, float value, HBDamageType damageType);

	void applyBuff(UBuff* buff);

	void applyDebuff(UBaseSkillComponent* buff);

	void apllyUniQueBuff(UBuff* buff);

	uint8 getAttributeValue(Attributes attributeName);

	void applyCondition(UBaseCondition* condtion);

	uint8 getCondtionCount();

	void knockDownCharacter(float duration);

	void updateHealthRegen(float regen);

private:


	void UpdateResources(float DeltaSeconds);


	Profession primaryProfession;
	Profession secondaryProfession;
	TMap<Condition, UBaseCondition*> m_condtionList;
	TMap<FString, UBuff*> m_BuffList;
	
	UPROPERTY(Replicated)
	USkill* skillList[8];
	int m_ConditionCount;
	int m_BuffCount;
	//removes condition from list if duration is expired
	void updateCondtion(float DeltaTime);

	//updates Regeneration based on De-buffs and conditions
	void updateRegeneration();
};
