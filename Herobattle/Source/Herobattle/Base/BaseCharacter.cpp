// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	m_MaxHealth = 480;
	m_MaxMana = 25;
	m_Health = 240;
	m_Mana = 10.0f;
	m_HealthRegeneration = 0;
	m_ManaRegeneration = 2;

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
	if (m_Health >= m_MaxHealth){
		m_Health = m_MaxHealth;
	}
	else
	{
		m_Health += DeltaSeconds * (m_HealthRegeneration * 2.0f);
	}
	
	if (m_Mana >= m_MaxMana){
		m_Mana = m_MaxMana;
	}
	else
	{
		m_Mana += DeltaSeconds * (m_ManaRegeneration / 3.0f);
	}

}