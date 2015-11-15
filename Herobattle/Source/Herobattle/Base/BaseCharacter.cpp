// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseCharacter.h"
#include "../Skills/Buff/BaseBuff.h"
#include "../Skills/Condition/BaseCondition.h"
#include "UnrealNetwork.h"


ABaseCharacter::ABaseCharacter()
{

	m_MaxHealth = 480;
	m_MaxMana = 25;
	m_Health = 240;
	m_Mana = 10.0f;
	m_HealthRegeneration = 0;
	m_ManaRegeneration = 2;
	m_conditionCount = 0;

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

void ABaseCharacter::UseSkill_Implementation(ABaseCharacter* Target, int32 SkillSlot)
{
}

void ABaseCharacter::ChangeHealth(float value)
{
	m_Health += value;
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
	if (m_Health < 0)
	{
		m_Health = 0;
	}
}

void ABaseCharacter::ChangeMana(float value)
{
	m_Mana += value;
	if (m_Mana > m_MaxMana)
	{
		m_Mana = m_MaxMana;
	}
	if (m_Mana < 0)
	{
		m_Mana = 0;
	}
}

void ABaseCharacter::heal(float value)
{

}

void ABaseCharacter::damage(float value, HBDamageType damageType)
{

}

void ABaseCharacter::applyBuff(UBaseBuff* buff)
{

}

void ABaseCharacter::applyDebuff(UBaseBuff* buff)
{

}

void ABaseCharacter::apllyUniQueBuff(UBaseBuff* buff)
{

}

uint8 ABaseCharacter::getAttributeValue(Attributes attributeName)
{
	return 0;
}

void ABaseCharacter::applyCondition(UBaseCondition* condtion)
{
	m_conditionCount++;
}

uint8 ABaseCharacter::getCondtionCount()
{
	return m_conditionCount;
}

void ABaseCharacter::knockDownCharacter(float duration)
{

}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter, m_MaxHealth);
	DOREPLIFETIME(ABaseCharacter, m_MaxMana);
	DOREPLIFETIME(ABaseCharacter, m_Health);
	DOREPLIFETIME(ABaseCharacter, m_Mana);
	DOREPLIFETIME(ABaseCharacter, m_ManaRegeneration);
	DOREPLIFETIME(ABaseCharacter, m_HealthRegeneration);
}
