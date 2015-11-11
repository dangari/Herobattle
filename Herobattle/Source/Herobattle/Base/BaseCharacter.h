// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/Profession.h"
#include "../Enum/SkillEnums.h"
#include "../Skills/Components/BaseSkillComponent.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */

class UBaseBuff;
class UBaseCondition;

UENUM(BlueprintType)
enum class TeamColor : uint8
	{ RED, BLUE };


UCLASS()
class HEROBATTLE_API ABaseCharacter: public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	~ABaseCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterProperties)
	TeamColor ETeam;

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

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BluePrintNativeEvent, BlueprintCallable, Category = Mechanics)
	void UseSkill(ABaseCharacter* Target, int32 SkillSlot);

	UFUNCTION(BlueprintCallable, Category = Meachnics)
	void ChangeHealth(float value);

	UFUNCTION(BlueprintCallable, Category = Meachnics)
	void ChangeMana(float value);

// this Functions get called by Skills
	void heal(float value);

	void damage(float value, HBDamageType damageType);

	void applyBuff(UBaseBuff* buff);

	void applyDebuff(UBaseBuff* buff);

	void apllyUniQueBuff(UBaseBuff* buff);

	uint8 getAttributeValue(Attributes attributeName);

	void applyCondition(UBaseCondition* condtion);

private:

	Profession primaryProfession;
	Profession secondaryProfession;

	void UpdateResources(float DeltaSeconds);

};
