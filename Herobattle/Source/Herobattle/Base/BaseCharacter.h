// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Base/Profession.h"
#include "BaseCharacter.generated.h"
/**
 * 
 */
UCLASS()
class HEROBATTLE_API ABaseCharacter: public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
	~ABaseCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float maxMana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	float mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 manaRegeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterProperties)
	int32 healthRegeneration;

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
