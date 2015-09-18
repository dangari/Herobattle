// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	maxHealth = 480;
	maxMana = 25;
	health = 240;
	mana = 10.0f;
	healthRegeneration = 0;
	manaRegeneration = 2;

}

ABaseCharacter::~ABaseCharacter()
{
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateResources(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABaseCharacter::UpdateResources(float DeltaSeconds){
	if (health >= maxHealth){
		health = maxHealth;
	}
	else
	{
		health += DeltaSeconds * (healthRegeneration * 2.0f);
	}
	
	if (mana >= maxMana){
		mana = maxMana;
	}
	else
	{
		mana += DeltaSeconds * (manaRegeneration / 3.0f);
	}

}