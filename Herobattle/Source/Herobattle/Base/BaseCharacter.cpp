// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	maxHealth = 480.0f;
	maxMana = 20.0f;
	health = 250;
	mana = maxMana;
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

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}