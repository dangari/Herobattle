// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseCharacter.h"
#include "../Skills/Buff/Buff.h"
#include "../Skills/Condition/BaseCondition.h"
#include "UnrealNetwork.h"
#include "HerobattleGameMode.h"
#include "SkillMessages.h"


ABaseCharacter::ABaseCharacter()
:m_MaxHealth(480),
m_MaxMana(25),
m_Health(240),
m_Mana(10.0f),
m_HealthRegeneration(0),
m_ManaRegeneration(4),
m_ConditionCount(0),
m_BuffCount(0)
{
}

ABaseCharacter::~ABaseCharacter()
{
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		AHerobattleGameMode* gm = (AHerobattleGameMode*)(GetWorld()->GetAuthGameMode());
		skillList[0] = gm->skillList[0];
		skillList[1] = gm->skillList[1];
		skillList[2] = gm->skillList[2];
		messages = NewObject<USkillMessages>();
	}
	else
	{

	}

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCondtion(DeltaTime);
	UpdateRegeneration();
	UpdateResources(DeltaTime);
	UpdateSkillCooldown(DeltaTime);
	UpdateBuffs(DeltaTime);

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


void ABaseCharacter::UpdateCondtion(float DeltaTime)
{
	for (auto& condi : m_condtionList)
	{
		condi.Value->duration -= DeltaTime;
		if (condi.Value->duration <= 0)
		{
			m_condtionList.Remove(condi.Key);
		}
			
	}
}

void ABaseCharacter::UpdateRegeneration()
{
	m_HealthRegeneration = 0;
	for (auto& condi : m_condtionList)
	{
		m_HealthRegeneration +=  condi.Value->regeneration;
	}
	//add buff
	// add gate at -/+10 regeneration
}

bool ABaseCharacter::skillManaCost(float value)
{
	if ((m_Mana - value) < 0)
	{
		messages->registerMessage(TEXT("Not enough mana"), MessageType::SKILLERROR);
		return false;
	}
	else
	{
		m_Mana -= value;
		return true;
	}
}

bool ABaseCharacter::skillIsOnCooldown(int slot)
{
	if (skillcooldowns[slot].currentCooldown <= 0.001f)
		return false;
	else
	{
		messages->registerMessage(TEXT("skill is on cooldown"), MessageType::SKILLERROR);
		return true;
	}
}

void ABaseCharacter::UpdateSkillCooldown(float deltaTime)
{
	for (auto& cooldown : skillcooldowns)
	{
		cooldown.currentCooldown -= deltaTime;
		if (cooldown.currentCooldown <= 0)
			cooldown.currentCooldown = 0.0f;
	}
}

void ABaseCharacter::UpdateBuffs(float deltaTime)
{
	for (auto& buff : m_BuffList)
	{
		buff.Value->updateBuff(deltaTime);
		if (buff.Value->isExpired())
		{
			m_BuffList.Remove(buff.Key);
			m_BuffCount--;
		}
	}
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


struct FSkillCooldown ABaseCharacter::getCooldown(uint8 slot)
{
	if (slot >= 0 && slot <= 7)
	{
		return skillcooldowns[slot];
	}
	FSkillCooldown temp;
	return temp;

}



bool ABaseCharacter::UseSkill(ABaseCharacter* target, int32 slot)
{
	if (HasAuthority())
	{
		USkill* skill = skillList[slot];
		int newMana = m_Mana - skill->manaCost;
		if (!skillIsOnCooldown(slot) && skillManaCost(skill->manaCost))
		{
			skillcooldowns[slot].currentCooldown = skill->recharge;
			skillcooldowns[slot].maxCooldown = skill->recharge;
			currentSkill.registerSkill(skill);
			UE_LOG(LogTemp, Warning, TEXT("Skill name: %s"), *(currentSkill.skillName));
			bool b = skill->run(target, this);
			return true;
		}
	}
	return false;
}


void ABaseCharacter::heal(ABaseCharacter* caster, float value, bool withBuff)
{

	if (withBuff)
	{
		for (auto& buff : m_BuffList)
		{
			buff.Value->run(caster, this, value);
		}
	}
	m_Health += value;
	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;
}


void ABaseCharacter::damage(ABaseCharacter* caster, float value, HBDamageType damageType,bool withBuff)
{
	if (withBuff)
	{
		for (auto& buff : m_BuffList)
		{
			buff.Value->run(caster, this, -1*value);
		}
	}
	m_Health -= value;
	// test if target is dead
	if (m_Health < 0)
		m_Health = m_MaxHealth;
}

void ABaseCharacter::applyBuff(UBuff* buff)
{
	if (!(m_BuffList.Contains(buff->getName())))
		m_BuffCount++;
	m_BuffList.Add(buff->getName(), buff);
}

void ABaseCharacter::applyDebuff(UBaseSkillComponent* buff)
{

}

void ABaseCharacter::apllyUniQueBuff(UBuff* buff)
{

}

uint8 ABaseCharacter::getAttributeValue(Attributes attributeName)
{
	return 0;
}

void ABaseCharacter::applyCondition(UBaseCondition* condition)
{
	if (!(m_condtionList.Contains(condition->condition)))
		m_ConditionCount++;
	m_condtionList.Add(condition->condition, condition);
	
}

uint8 ABaseCharacter::getCondtionCount()
{
	return m_ConditionCount;
}

void ABaseCharacter::knockDownCharacter(float duration)
{

}

void ABaseCharacter::updateHealthRegen(float regen)
{
	m_HealthRegeneration += regen;
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
	DOREPLIFETIME(ABaseCharacter, currentSkill);
	DOREPLIFETIME(ABaseCharacter, messages);
	DOREPLIFETIME(ABaseCharacter, skillcooldowns);
}
