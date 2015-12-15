// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/Profession.h"
#include "../Enum/SkillEnums.h"
#include "../Skills/Components/BaseSkillComponent.h"
#include "Skills/Skill.h"
#include "Weapon.h"
#include "Enum/CharacterEnums.h"
#include "SkillContainer.h"
#include "AI/CharacterState.h"
#include "BaseCharacter.generated.h"




/**
 * 
 */

class UBuff;
class UBaseCondition;
class USkillMessages;





USTRUCT(BlueprintType)
struct FSkillCooldown
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	float currentCooldown = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	float maxCooldown = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skills)
	float additionalCoolDown = 0.f;
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
	void ChangeMana(float value);

	UFUNCTION(BlueprintCallable, Category = Skills)
	struct FSkillCooldown getCooldown(uint8 slot);

	UFUNCTION(BlueprintCallable, Category = Skills)
	struct FSkillHUD getCurrentCast();

	UFUNCTION(BlueprintCallable, Category = Skills)
	bool isCastingSkill(FString message = TEXT("NOTHING"));


// this Functions get called by Skills
	void heal(ABaseCharacter* caster, float value, bool withBuff = true);

	void damage(ABaseCharacter* caster, float value, HBDamageType damageType, bool withBuff = true);

	void applyBuff(UBuff* buff);

	void applyDebuff(UBaseSkillComponent* buff);

	void apllyUniQueBuff(UBuff* buff);

	uint8 getAttributeValue(Attributes attributeName);

	void applyCondition(UBaseCondition* condtion);

	uint8 getCondtionCount();

	HBCharacterState getState();

	FWeapon getWeapon();

	SkillType getCurrentSkillType();

	void knockDownCharacter(float duration);

	void setCoolDown(float time, CoolDownType cdType);

	bool isEnemy(TeamColor team);
	bool hasCondition(Condition condition);

	//Creates a state of the character
	FCharacterState AiExtractor(ABaseCharacter* character);

	//test if the skill is on cooldown
	bool skillIsOnCooldown(int slot);


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

	UPROPERTY(Replicated)
	USkill* skillList[8];

	

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

	void updateHealthRegen(float regen);

	void RunBuffsAfterSkill();

	//check if Character is using autotack
	bool isAttacking();

	//checks if enough mana is remaining for the skill
	//if enough mana is remaining the mana costs get abstracted from the mana of the character
	bool skillManaCost(float value);

	void setCoolDownAll(float Time);
	void setInterruptCoolDown(float Time);
	void setCurrentSkillCoolDown(float Time);
	void setAttributeCoolDown(float Time);

	TArray<Condition> getConditions();

	float getAirDistance(APawn* pawn);

	float getWalkDistance(APawn* pawn);
	

	Profession primaryProfession;
	Profession secondaryProfession;
	TMap<Condition, UBaseCondition*> m_condtionList;
	TMap<FString, UBuff*> m_BuffList;
	TMap<Attributes, uint8> attrList;

	UPROPERTY(Replicated)
	FSkillCooldown skillcooldowns[8];
	
	
	int m_ConditionCount;
	int m_BuffCount;
	int m_DebuffCount;

	UPROPERTY(Replicated)
	FWeapon weapon;

	bool useAutoAttack;
	HBCharacterState state = HBCharacterState::IDLE;
};
