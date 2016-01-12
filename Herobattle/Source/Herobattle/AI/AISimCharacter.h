// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/BaseCharacter.h"
#include "HBBlackboard.h"
#include "Base/CharacterProperties.h"
#include "Base/SkillContainer.h"
#include "AISimCharacter.generated.h"

/**
 * 
 */
class UBuff;
class UBaseCondition;
class USkillMessages;
class USkill;

UCLASS()
class HEROBATTLE_API UAISimCharacter : public UObject
{
	GENERATED_BODY()
	
public:
	UAISimCharacter();
	~UAISimCharacter();

	void init(FCharacterState state);
	void init(FCharacterProperties character);

	void simulate(TArray<USimAction*> actionList, TMap<FString, FCharacterState> characterList, float DeltaTime);

	void simulateAction(USimAction* action, TMap<FString, FCharacterState> &characterList, float duration);



private:

	void applyCondition(TArray<Condition> conditions);
	void applyDummyBuff();	

	void simulateAutoAttack();
	
	int getSlot(USkill* skill);


	FVector m_location;
	int m_attackers;
	int m_caster;

	bool m_isCasting = false;
	bool m_isAutoAttacking = false;
	bool m_isBuffed = false;
	bool m_isHexed = false;
	bool m_hasStance = false;


public:
	void Tick(float DeltaSeconds);




	UFUNCTION(BlueprintCallable, Category = Mechanics)
	bool UseSkill(UAISimCharacter* Target, int32 SkillSlot);


	UFUNCTION(BlueprintCallable, Category = Meachnics)
	void ChangeMana(float value);


	UFUNCTION(BlueprintCallable, Category = Skills)
	bool isCastingSkill(FString message = TEXT("NOTHING"));

	UFUNCTION(BlueprintCallable, Category = Meachnics)
	FAdrenaline GetCurrentAdrenaline(uint8 slot);





	// this Functions get called by Skills
	void heal(UAISimCharacter* caster, float value, bool withBuff = true);

	void damage(UAISimCharacter* caster, float value, HBDamageType damageType, bool withBuff = true);

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

	FCharacterProperties getProperties();

	SkillType getCurrentSkillType();

	UAISimCharacter* clone();

	void knockDownCharacter(float duration);

	void Remove(RemoveType type, int count);

	void setCoolDown(float time, CoolDownType cdType);

	void setState(HBCharacterState state, UAISimCharacter* target);

	bool isEnemy(TeamColor team);

	bool hasCondition(Condition condition);

	bool canUseSkill(int slot);

	//Creates a state of the character
	FCharacterState AiExtractor(UAISimCharacter* character);

	//test if the skill is on cooldown
	bool skillIsOnCooldown(int slot);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterProperties)
	FString m_Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float m_MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float m_MaxMana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float m_Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float m_Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 m_ManaRegeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 m_HealthRegeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Info)
	FSkillStatus currentSkill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Info)
	USkillMessages* messages;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Info)
	UAISimCharacter* selectedTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Info)
	TeamColor ETeam;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Info)
	ProfessionName proffession;

	UPROPERTY()
	TArray<USkill*> skillList;



protected:
	// starts or stop AutoAttack
	UFUNCTION(Server, WithValidation, reliable)
	void setAttack(bool b);

	UFUNCTION(Server, WithValidation, reliable)
	void stopCurrenSkill();

	void getBuffs();

	void Update(float DeltaTime);



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

	bool RunBuff(Trigger trigger, UAISimCharacter* caster, int value = 0);

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

	UPROPERTY()
	FSkillCooldown skillcooldowns[8];

	UPROPERTY()
	FAdrenaline m_AdrenalineList[8];

	int m_ConditionCount;
	int m_BuffCount;
	int m_DebuffCount;

	float m_NewAttackSpeed;
	float m_AttackSpeed;
	float m_leftAttackTime;
	float m_DefaultMovementSpeed;
	float m_MovementSpeed;

	UPROPERTY()
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
