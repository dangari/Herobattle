// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/Profession.h"
#include "../Enum/SkillEnums.h"
#include "../Skills/Components/BaseSkillComponent.h"
#include "Skills/Skill.h"
#include "Weapon.h"
#include "Enum/CharacterEnums.h"
#include "BaseCharacter.generated.h"




/**
 * 
 */

class UBuff;
class UBaseCondition;
class USkillMessages;



USTRUCT()
struct FSkillHUD
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	FString skillName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	float leftCastTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	float castTime;
};

USTRUCT()
struct FSkillStatus
{
	GENERATED_USTRUCT_BODY()

	void registerSkill(USkill* skill,ABaseCharacter* target, int32 slot)
	{
		castingSkill = true;
		this->skill = skill;
		leftCastTime = skill->castTime;
		skillName = skill->name;
		this->target = target;
		this->slot = slot;
		castTime = skill->castTime;
	}

	UPROPERTY()
	FString skillName;
	UPROPERTY()
	float leftCastTime;
	UPROPERTY()
	float castTime;
	UPROPERTY()
	USkill* skill;
	UPROPERTY()
	ABaseCharacter* target;
	UPROPERTY()
	int32 slot;

	UPROPERTY()
	bool castingSkill;
};

USTRUCT(BlueprintType)
struct FSkillCooldown
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	float currentCooldown = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	float maxCooldown = 0.f;
};


UCLASS()
class HEROBATTLE_API ABaseCharacter: public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	~ABaseCharacter();
	
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

	UFUNCTION(BlueprintCallable, Category = Skills)
	struct FSkillCooldown getCooldown(uint8 slot);

	UFUNCTION(BlueprintCallable, Category = Skills)
	struct FSkillHUD getCurrentCast();

	UFUNCTION(BlueprintCallable, Category = Skills)
	bool isCastingSkill();


// this Functions get called by Skills
	void heal(ABaseCharacter* caster, float value, bool withBuff = true);

	void damage(ABaseCharacter* caster, float value, HBDamageType damageType, bool withBuff = true);

	void applyBuff(UBuff* buff);

	void applyDebuff(UBaseSkillComponent* buff);

	void apllyUniQueBuff(UBuff* buff);

	uint8 getAttributeValue(Attributes attributeName);

	void applyCondition(UBaseCondition* condtion);

	uint8 getCondtionCount();

	void knockDownCharacter(float duration);

	void updateHealthRegen(float regen);


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

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Info)
	FSkillStatus currentSkill;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Info)
	USkillMessages* messages;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = Info)
	ABaseCharacter* selectedTarget;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = Info)
	TeamColor ETeam;

protected:
	// starts or stop AutoAttack
	UFUNCTION(Server, WithValidation, reliable)
	void setAttack(bool b);

	UFUNCTION(Server, WithValidation, reliable)
	void stopCurrenSkill();

private:

	// updates health and mana
	void UpdateResources(float DeltaSeconds);

	//removes condition from list if duration is expired
	void UpdateCondtion(float DeltaTime);

	//updates Regeneration based on De-buffs and conditions
	void UpdateRegeneration();
	
	//updates skill cooldown
	void UpdateSkillCooldown(float deltaTime);

	//checks if buffs still active if not remove buff expired buffs
	void UpdateBuffs(float deltaTime);

	//updates the skill and runs the skill if cast time < 0
	void UpdateCurrentSkill(float deltaTime);

	void UpdateAtack(float deltaTime);



	//check if Character is using autotack
	bool isAttacking();

	//checks if enough mana is remaining for the skill
	//if enough mana is remaining the mana costs get abstracted from the mana of the character
	bool skillManaCost(float value);

	//test if the skill is on cooldown
	bool skillIsOnCooldown(int slot);

	bool isEnemy(TeamColor team);

	

	Profession primaryProfession;
	Profession secondaryProfession;
	TMap<Condition, UBaseCondition*> m_condtionList;
	TMap<FString, UBuff*> m_BuffList;
	

	UPROPERTY(Replicated)
	USkill* skillList[8];
	UPROPERTY(Replicated)
	FSkillCooldown skillcooldowns[8];
	
	int m_ConditionCount;
	int m_BuffCount;

	UPROPERTY(Replicated)
	FWeapon weapon;

	bool useAutoAttack;
};
