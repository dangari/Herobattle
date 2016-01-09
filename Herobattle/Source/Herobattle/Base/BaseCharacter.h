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
struct FAdrenaline
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 currentAdrenaline = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 maxAdrenaline = 0;
};


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

USTRUCT(BlueprintType)
struct FBuffList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<FString, UBuff*> m_BuffList;
};


UCLASS()
class HEROBATTLE_API ABaseCharacter: public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	~ABaseCharacter();
	
	UFUNCTION(BlueprintCallable, Category = Mechanics)
	void InitializeSkills();

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

	UFUNCTION(BlueprintCallable, Category = Meachnics)
	FAdrenaline GetCurrentAdrenaline(uint8 slot);

	


// this Functions get called by Skills
	void heal(ABaseCharacter* caster, float value, bool withBuff = true);

	void damage(ABaseCharacter* caster, float value, HBDamageType damageType, bool withBuff = true);

	void applyBuff(UBuff* buff, Trigger trigger);

	void applyDebuff(UBaseSkillComponent* buff);

	void apllyUniQueBuff(UBuff* buff);

	uint8 getAttributeValue(Attributes attributeName);

	void applyCondition(UBaseCondition* condtion);

	void applyManaReduction(int value);

	void applyDamageReduction(float value);

	void applyRegneration(int value, RegnerationType type);

	void applyAttackSpeed(float value);

	void applyMovementSpeed(float value);

	uint8 getCondtionCount();

	uint8 getDebuffCount();

	HBCharacterState getState();

	FWeaponValues getWeapon();

	uint8 getBuffCount();

	SkillType getCurrentSkillType();

	ABaseCharacter* clone();

	void knockDownCharacter(float duration);

	void Remove(RemoveType type, int count);

	void setCoolDown(float time, CoolDownType cdType);

	void setState(HBCharacterState state, ABaseCharacter* target);

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

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = Info)
	ProfessionName proffession;

	UPROPERTY(Replicated)
	USkill* skillList[8];

	

protected:
	// starts or stop AutoAttack
	UFUNCTION(Server, WithValidation, reliable)
	void setAttack(bool b);

	UFUNCTION(Server, WithValidation, reliable)
	void stopCurrenSkill();

	void getBuffs();

private:

	void InitializeAdrenaline();
	
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

	void UpdateAttack(float deltaTime);

	void updateHealthRegen(float regen);

	void UpdateAdrenaline();

	void UpdateModifier();

	bool RunBuff(Trigger trigger, ABaseCharacter* caster, int value = 0);

	//check if Character is using autotack
	bool isAttacking();

	//checks if enough mana is remaining for the skill
	//if enough mana is remaining the mana costs get abstracted from the mana of the character
	bool skillCost(int slot);

	void useAdrenaline(int slot);

	void setCoolDownAll(float Time);
	void setInterruptCoolDown(float Time);
	void setCurrentSkillCoolDown(float Time);
	void setAttributeCoolDown(float Time);

	TArray<Condition> getConditions();

	float getAirDistance(APawn* pawn);

	float getWalkDistance(APawn* pawn);

protected:

	Profession primaryProfession;
	Profession secondaryProfession;

	UPROPERTY()
	TMap<Condition, UBaseCondition*> m_condtionList;

	UPROPERTY()
	TMap<FString, Trigger> m_BuffList;

	UPROPERTY()
	TMap<Trigger, FBuffList> m_CompleteBuffList;
	
	UPROPERTY()
	TMap<Attributes, uint8> attrList;

	UPROPERTY(Replicated)
	FSkillCooldown skillcooldowns[8];
	
	UPROPERTY(Replicated)
	FAdrenaline m_AdrenalineList[8];
	
	int m_ConditionCount;
	int m_BuffCount;
	int m_DebuffCount;

	float m_NewAttackSpeed;
	float m_AttackSpeed;
	float m_leftAttackTime;
	float m_DefaultMovementSpeed;
	float m_MovementSpeed;

	UPROPERTY(Replicated)
	FWeaponValues weapon;

	bool useAutoAttack;
	HBCharacterState m_State = HBCharacterState::IDLE;

	UPROPERTY()
	int32 m_ManaReduction;
	UPROPERTY()
	float m_DamageReduction;
	UPROPERTY()
	int32 m_HealthBuffRegneration;
	UPROPERTY()
	int32  m_ManaBuffRegneration;
};
