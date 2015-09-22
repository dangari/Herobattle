// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/Profession.h"
#include "BaseCharacter.generated.h"
/**
 * 
 */
enum Team{ RED, BLUE };
UCLASS()
class HEROBATTLE_API ABaseCharacter: public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	~ABaseCharacter();
	
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

private:


	Profession primaryProfession;
	Profession secondaryProfession;

	void UpdateResources(float DeltaSeconds);

};
