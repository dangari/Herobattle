// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "AISimCharacter.h"
#include "Skills/Condition/BaseCondition.h"
#include "Skills/Buff/Buff.h"
#include "Skills/XMLSkillReader.h"
#include "CharacterState.h"




UAISimCharacter::UAISimCharacter()
{

}

UAISimCharacter::~UAISimCharacter()
{

}

void UAISimCharacter::init(FCharacterState state)
{
	ETeam = state.ETeam;
	weapon = state.weapon;
	m_location = state.location;
	m_AirDistance = state.airDistance;
	m_WalkDistance = state.walkDistance;

	m_MaxHealth = state.self->m_MaxHealth;
	m_Health = state.self->m_Health;
	m_State = state.state;

	m_isCasting = state.isCasting;
	m_isAutoAttacking = state.isAutoAttacking;
	m_isBuffed = state.isBuffed;
	m_isHexed = state.isHexed;

	m_hasStance = state.hasStance;

	attrList = state.attrList;

	applyCondition(state.conditions);

	if (m_isBuffed)
	{
		applyDummyBuff();
	}
	
}



void UAISimCharacter::init(FCharacterProperties properties)
{
	m_MaxHealth = properties.m_MaxHealth;
	m_Health = properties.m_Health;
	m_MaxMana = properties.m_MaxMana;
	m_Mana = properties.m_Mana;
	m_ManaRegeneration = properties.m_ManaRegeneration;
	ETeam = properties.ETeam;
	proffession = properties.proffession;
	m_BuffList = properties.m_BuffList;
	attrList = properties.attrList;
	weapon = properties.weapon;
	m_State = properties.m_State;
	m_ManaReduction = properties.m_ManaReduction;
	m_DamageReduction = properties.m_DamageReduction;
	m_HealthBuffRegneration = properties.m_HealthBuffRegneration;
	m_ManaBuffRegneration = properties.m_ManaBuffRegneration;
	m_location = properties.location;

	UAISimCharacter* dummy = NewObject<UAISimCharacter>();
	dummy->init(properties.selectedTarget->AiExtractorSim(this));
	selectedTarget = dummy;
	


	for (auto& elem : properties.m_CompleteBuffList)
	{
		FBuffList buffList = elem.Value;
		FBuffList newBuffList;
		Trigger trigger = elem.Key;
		for (auto& item : buffList.m_BuffList)
		{
			UBuff* buff = item.Value;
			UBuff* newBuff = buff->copy();
			newBuffList.m_BuffList.Add(newBuff->m_Name, newBuff);
		}
		m_CompleteBuffList.Add(trigger, newBuffList);

	}

	skillList = properties.skillList;


	for (auto& elem : properties.m_condtionList)
	{
		UBaseCondition* condi = elem.Value;
		UBaseCondition* condition = UBaseCondition::MAKE(condi->condition, condi->currentDuration);
		UAISimCharacter::applyCondition(condi);
	}
	Update(0.f);
}

void UAISimCharacter::simulate(TArray<USimAction*> actionList, TMap<FString, FCharacterState> characterList, float DeltaTime)
{
	float duration = 0.f;
	for (auto& action : actionList)
	{
		if (duration + action->time > DeltaTime)
		{

			simulateAction(action, characterList, duration);

			duration += action->time - duration;
		}
		else
		{
			switch (action->action)
			{
			case AIAction::IDLE:
				m_State = HBCharacterState::IDLE;
				break;
			case AIAction::AUTOATACK:
				m_State = HBCharacterState::AUTOATTACK;
				break;
			case AIAction::SKILL:
				currentSkill.castingSkill = true;
				currentSkill.castTime = action->skill->properties.castTime;
				currentSkill.leftCastTime = currentSkill.castTime - (action->time - duration);
				break;
			default:
				break;
			}
		}
	}
}

void UAISimCharacter::simulateAction(USimAction* action, TMap<FString, FCharacterState> &characterList, float duration)
{
	if (action->action == AIAction::SKILL)
	{
		if (action->ownerName.Equals(m_Name))
		{
			RunBuff(Trigger::BEFORECAST, this);
			if (skillCost(getSlot(action->skill)))
			{
				action->skill->runSim(NewObject<UAISimCharacter>(), this);
				RunBuff(Trigger::AFTERCAST, this);
				skillcooldowns[getSlot(action->skill)].maxCooldown = action->skill->properties.recharge;
				skillcooldowns[getSlot(action->skill)].currentCooldown = action->skill->properties.recharge;
			}
		}
		else
		{
			UAISimCharacter* dummyCharacter = NewObject<UAISimCharacter>();
			dummyCharacter->init(*characterList.Find(action->ownerName));
			action->skill->runSim(this, dummyCharacter);
		}
	}
	if (action->action == AIAction::AUTOATACK)
	{
		if (action->ownerName.Equals(m_Name))
		{
			simulateAutoAttack();
		}
		else
		{
			FCharacterState owner = *characterList.Find(action->ownerName);
			damage(NewObject<UAISimCharacter>(), owner.weapon.getDamage(), HBDamageType::PHYSICAL);
		}
	}
	Update(action->time - duration);
}

void UAISimCharacter::applyCondition(TArray<Condition> conditions)
{
	for (auto& condi : conditions)
	{
		UBaseCondition* simCondi = NewObject<UBaseCondition>();
		simCondi->init(condi, 10);
		UAISimCharacter::applyCondition(simCondi);
	}
}

void UAISimCharacter::applyDummyBuff()
{
	UBuff* dummyBuff = NewObject<UBuff>();
	dummyBuff->initDummyBuff();
	applyBuff(dummyBuff, Trigger::NONE);
}




void UAISimCharacter::simulateAutoAttack()
{
	UpdateAdrenaline();
	m_State = HBCharacterState::AUTOATTACK;
}

int UAISimCharacter::getSlot(USkill* skill)
{
	for (int i = 0; i < 8; i++)
	{
		if (skillList[i]->name.Equals(skill->name))
		{
			return i;
		}
	}
	return 0;
}


void UAISimCharacter::Tick(float DeltaTime)
{
		Update(DeltaTime);
}

void UAISimCharacter::Update(float DeltaTime)
{
	RunBuff(Trigger::NONE, this);
	UpdateModifier();
	UpdateCondtion(DeltaTime);
	UpdateRegeneration();
	UpdateResources(DeltaTime);
	UpdateSkillCooldown(DeltaTime);
	UpdateBuffs(DeltaTime);
	if (currentSkill.castingSkill)
	{
		UpdateCurrentSkill(DeltaTime);
	}

	if (m_State == HBCharacterState::AUTOATTACK)
	{
		UpdateAttack(DeltaTime);
	}
}


void UAISimCharacter::stopCurrenSkill_Implementation()
{
	if (isCastingSkill())
	{
		currentSkill.castingSkill = false;
		m_State = HBCharacterState::IDLE;
	}
}
bool UAISimCharacter::stopCurrenSkill_Validate()
{
	return true;
}



void UAISimCharacter::InitializeAdrenaline()
{
	int i = 0;
	for (auto& skill : skillList)
	{
		if (skill->properties.costType == CostType::ADRENALINE)
		{
			m_AdrenalineList[i].maxAdrenaline = skill->properties.cost;
		}
		i++;
	}
}


void UAISimCharacter::UpdateResources(float DeltaSeconds){


	m_Health += DeltaSeconds * ((m_HealthRegeneration)* 2.0f);
	m_Mana += DeltaSeconds * (m_ManaRegeneration / 3.0f);

	if (m_Health >= m_MaxHealth){
		m_Health = m_MaxHealth;
	}

	if (m_Mana >= m_MaxMana){
		m_Mana = m_MaxMana;
	}

	if (m_Mana < 0)
		m_Mana = 0;
	if (m_Health < 0)
		m_Health = m_MaxHealth;
	m_HealthBuffRegneration = 0;
}


void UAISimCharacter::UpdateCondtion(float DeltaTime)
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

void UAISimCharacter::UpdateRegeneration()
{
	m_HealthRegeneration = 0;
	for (auto& condi : m_condtionList)
	{
		m_HealthRegeneration += condi.Value->regeneration;
	}
	m_HealthRegeneration += m_HealthBuffRegneration;

	if (m_HealthRegeneration > 10)
		m_HealthRegeneration = 10;
	else if (m_HealthRegeneration < -10)
	{
		m_HealthRegeneration = -10;
	}

	//add buff
	// add gate at -/+10 regeneration
}

bool UAISimCharacter::skillCost(int slot)
{
	CostType type = skillList[slot]->properties.costType;
	int value = skillList[slot]->properties.cost;
	if (type == CostType::MANA)
	{
		if (((m_Mana + m_ManaReduction) - value) < 0)
		{
			return false;
		}
		else
		{
			float manaCost = value - m_ManaReduction;
			if (manaCost < 0)
				manaCost = 0;
			m_Mana -= manaCost;
			return true;
		}
	}
	else if (type == CostType::ADRENALINE)
	{
		if (m_AdrenalineList[slot].currentAdrenaline == m_AdrenalineList[slot].maxAdrenaline)
		{
			useAdrenaline(slot);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}




void UAISimCharacter::useAdrenaline(int slot)
{
	m_AdrenalineList[slot].currentAdrenaline = 0;
	for (auto& adrenaline : m_AdrenalineList)
	{
		if (adrenaline.currentAdrenaline > 0)
			adrenaline.currentAdrenaline--;
	}
}

void UAISimCharacter::setCoolDownAll(float Time)
{

}

void UAISimCharacter::setInterruptCoolDown(float Time)
{
	int slot = currentSkill.slot;
	skillcooldowns[slot].currentCooldown = Time;
	skillcooldowns[slot].maxCooldown = Time;
}

void UAISimCharacter::setCurrentSkillCoolDown(float Time)
{
	int slot = currentSkill.slot;
	skillcooldowns[slot].additionalCoolDown = Time;
}

void UAISimCharacter::setAttributeCoolDown(float Time)
{

}

bool UAISimCharacter::skillIsOnCooldown(int slot)
{
	if (skillcooldowns[slot].currentCooldown <= 0.001f)
		return false;
	else
	{
		return true;
	}
}

TArray<Condition> UAISimCharacter::getConditions()
{
	TArray<Condition> conditions;
	for (auto& condi : m_condtionList)
	{
		conditions.Add(condi.Key);
	}
	return conditions;
}

float UAISimCharacter::getAirDistance(APawn* pawn)
{
	return 1.0f;
}

float UAISimCharacter::getWalkDistance(APawn* pawn)
{
	return 1.0f;
}

uint8 UAISimCharacter::getBuffCount()
{
	return m_BuffCount;
}

FCharacterProperties UAISimCharacter::getProperties()
{
	FCharacterProperties properties;
	properties.m_MaxHealth = m_MaxHealth;
	properties.m_Health = m_Health;
	properties.m_MaxMana = m_MaxMana;
	properties.m_Mana = m_Mana;
	properties.m_ManaRegeneration = m_ManaRegeneration;
	properties.ETeam = ETeam;
	properties.proffession = proffession;

	for (int i = 0; i < 8; i++)
	{
		properties.skillList[i] = skillList[i];
		properties.skillcooldowns[i] = skillcooldowns[i];
		properties.m_AdrenalineList[i] = m_AdrenalineList[i];
	}

	properties.m_condtionList = m_condtionList;
	properties.m_BuffList = m_BuffList;
	properties.m_CompleteBuffList = m_CompleteBuffList;
	properties.attrList = attrList;


	properties.weapon = weapon;
	properties.m_State = m_State;
	properties.m_ManaReduction = m_ManaReduction;
	properties.m_DamageReduction = m_DamageReduction;
	properties.m_HealthBuffRegneration = m_HealthBuffRegneration;
	properties.m_ManaBuffRegneration = m_ManaBuffRegneration;
	properties.location = m_location;

	return properties;

}

bool UAISimCharacter::isEnemy(TeamColor team)
{
	bool b = team == ETeam;
	return !b;
}

bool UAISimCharacter::hasCondition(Condition condition)
{
	return m_condtionList.Contains(condition);
}

bool UAISimCharacter::canUseSkill(int slot)
{
	if (skillList[slot]->properties.costType == CostType::ADRENALINE)
	{
		if (m_AdrenalineList[slot].currentAdrenaline == m_AdrenalineList[slot].maxAdrenaline)
			return true;

	}
	else if (skillList[slot]->properties.costType == CostType::MANA)
	{
		if (skillList[slot]->properties.cost < m_Mana + m_ManaReduction)
			return true;
	}
	return false;
}

FCharacterState UAISimCharacter::AiExtractor(UAISimCharacter* character)
{
	FCharacterState characterState;
	characterState.ETeam = ETeam;
	characterState.weapon = weapon;
	characterState.location = m_location;
	characterState.airDistance = (characterState.location - character->m_location).Size();
	characterState.isCasting = currentSkill.castingSkill;
	characterState.isAutoAttacking = useAutoAttack;
	if (m_BuffCount > 0)
		characterState.isBuffed = true;
	if (m_DebuffCount > 0)
		characterState.isHexed = true;
	characterState.conditions = getConditions();
	characterState.health = m_Health;
	characterState.skillState = currentSkill.copy();
	characterState.selectedTargetSim = selectedTarget;
	characterState.selfSim = this;
	characterState.state = m_State;
	if (m_State == HBCharacterState::CASTING)
		characterState.skillType = currentSkill.skill->properties.skillType;
	else
		characterState.skillType = SkillType::NONE;

	characterState.attrList = attrList;
	return characterState;
}

void UAISimCharacter::UpdateSkillCooldown(float deltaTime)
{
	for (auto& cooldown : skillcooldowns)
	{
		cooldown.currentCooldown -= deltaTime;
		if (cooldown.currentCooldown <= 0)
			cooldown.currentCooldown = 0.0f;
	}
}

void UAISimCharacter::UpdateBuffs(float deltaTime)
{
	for (auto& buffList : m_CompleteBuffList)
	{
		for (auto& buff : buffList.Value.m_BuffList)
		{
			buff.Value->updateBuff(deltaTime);
			if (buff.Value->isExpired())
			{
				m_BuffList.Remove(buff.Key);
				buffList.Value.m_BuffList.Remove(buff.Key);
				m_BuffCount--;
			}
		}
	}

}

void UAISimCharacter::UpdateCurrentSkill(float deltaTime)
{
	//currentSkill.leftCastTime -= deltaTime;
	//if (currentSkill.leftCastTime <= 0)
	//{
	//	currentSkill.skill->runSim(currentSkill.target, this);
	//	currentSkill.castingSkill = false;
	//	skillcooldowns[currentSkill.slot].currentCooldown = currentSkill.skill->properties.recharge;
	//	skillcooldowns[currentSkill.slot].maxCooldown = currentSkill.skill->properties.recharge + skillcooldowns[currentSkill.slot].additionalCoolDown;
	//	m_ManaReduction = 0;
	////	RunBuff(Trigger::AFTERCAST, this);
	//	if (currentSkill.skill->properties.skillType == SkillType::RANGEATTACK || currentSkill.skill->properties.skillType == SkillType::MELEEATTACK)
	//	{
	//		UpdateAdrenaline();
	//		m_State = HBCharacterState::AUTOATTACK;
	//	}
	//	else
	//	{
	//		m_State = HBCharacterState::IDLE;
	//	}
	//}
}

void UAISimCharacter::UpdateAttack(float deltaTime)
{
	m_leftAttackTime -= deltaTime;
	if (m_leftAttackTime <= 0)
	{
		int damage = weapon.getDamage();
		selectedTarget->damage(this, damage, HBDamageType::FIRE);
		UpdateAdrenaline();
		m_leftAttackTime = m_AttackSpeed;
	}
}

bool UAISimCharacter::setAttack_Validate(bool b)
{
	return true;
}

void UAISimCharacter::setAttack_Implementation(bool b)
{
	useAutoAttack = b;
	if (selectedTarget)
	{
		if (b)
			m_State = HBCharacterState::AUTOATTACK;
		else
			m_State = HBCharacterState::IDLE;
	}
	else
		m_State = HBCharacterState::IDLE;
}

bool UAISimCharacter::isAttacking()
{
	if (useAutoAttack && selectedTarget && selectedTarget->isEnemy(ETeam))
	{
		//FVector targetLocation = selectedTarget->GetActorLocation();
		//FVector myLocation = GetActorLocation();
// 		float distance = (targetLocation - myLocation).Size();
// 		UE_LOG(LogTemp, Warning, TEXT("Skill name: %f"), distance);
// 		if (distance <= weapon.range)
// 		{
// 			return true;
// 		}
// 		useAutoAttack = false;
// 		return false;
	}
	useAutoAttack = false;
	return false;
}


void UAISimCharacter::ChangeMana(float value)
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





bool UAISimCharacter::UseSkill(UAISimCharacter* target, int32 slot)
{

	USkill* skill = skillList[slot];
	UAISimCharacter* newTarget = target;

	//automatically sets target to self if the skill can be used on self and the target is enemy
	//also sets target to self if targettype is self
	if (skill->properties.targetType == TargetType::SELF || skill->properties.targetType == TargetType::SELFFRIEND && ((!target || target->isEnemy(ETeam))))
	{
		newTarget = this;
	}

	RunBuff(Trigger::BEFORECAST, this);

	if (newTarget && !skillIsOnCooldown(slot) && !isCastingSkill() && /*skill->isValidTarget(newTarget, this) &&*/ skillCost(slot))
	{
	//	currentSkill.registerSkill(skill, newTarget, slot);
		if (skill->properties.skillType == SkillType::MELEEATTACK || skill->properties.skillType == SkillType::RANGEATTACK)
		{
			currentSkill.castTime = m_AttackSpeed;
			currentSkill.leftCastTime = m_AttackSpeed;
		}
		m_State = HBCharacterState::CASTING;
		UE_LOG(LogTemp, Warning, TEXT("Skill name: %s"), *(currentSkill.skillName));
		useAutoAttack = false;
		//bool b = skill->run(target, this);
		return true;
	}

	return false;
}


bool UAISimCharacter::isCastingSkill(FString message)
{
	FString out = TEXT(" ");
	bool b = false;
	
	out = out.Append(message).Append(TEXT(" Server"));
	b = currentSkill.castingSkill;

	return b;
}

FAdrenaline UAISimCharacter::GetCurrentAdrenaline(uint8 slot)
{
	return m_AdrenalineList[slot];
}

void UAISimCharacter::heal(UAISimCharacter* caster, float value, bool withBuff)
{


	bool b = true;
	if (withBuff)
	{
		b = RunBuff(Trigger::HEAL, caster, value);
	}
	if (b)
	{
		m_Health += value;
	}
	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;

}


void UAISimCharacter::damage(UAISimCharacter* caster, float value, HBDamageType damageType, bool withBuff)
{

	bool b = true;
	if (withBuff)
	{
		b = RunBuff(Trigger::DAMAGE, caster, value);
	}
	if (b)
	{
		float damage = value - m_DamageReduction;
		if (damage > 0)
			m_Health -= damage;
	}
	// test if target is dead
	if (m_Health < 0)
		m_Health = m_MaxHealth;
	m_DamageReduction = 0;

}

void UAISimCharacter::applyBuff(UBuff* buff, Trigger trigger)
{

	if (!(m_BuffList.Contains(buff->getName())))
		m_BuffCount++;
	m_BuffList.Add(buff->getName(), trigger);
	if (m_CompleteBuffList.Contains(trigger))
	{
		m_CompleteBuffList.Find(trigger)->m_BuffList.Add(buff->getName(), buff);
	}
	else
	{
		FBuffList buffList;
		buffList.m_BuffList.Add(buff->getName(), buff);
		m_CompleteBuffList.Add(trigger, buffList);
	}
}

void UAISimCharacter::applyDebuff(UBaseSkillComponent* buff)
{

}

void UAISimCharacter::apllyUniQueBuff(UBuff* buff)
{

}

uint8 UAISimCharacter::getAttributeValue(Attributes attributeName)
{
	if (attrList.Contains(attributeName))
		return *(attrList.Find(attributeName));
	else
		return 0;
}

void UAISimCharacter::applyCondition(UBaseCondition* condition)
{
	if (!(m_condtionList.Contains(condition->condition)))
		m_ConditionCount++;
	m_condtionList.Add(condition->condition, condition);

}

void UAISimCharacter::applyManaReduction(int value)
{
	m_ManaReduction += value;
}

void UAISimCharacter::applyDamageReduction(float value)
{
	m_DamageReduction += value;
}

void UAISimCharacter::applyRegneration(int value, RegnerationType type)
{
	switch (type)
	{
	case RegnerationType::HEALTH:
		m_HealthBuffRegneration += value;
		break;
	case RegnerationType::MANA:
		m_ManaBuffRegneration += value;
		break;
	default:
		break;
	}
}

void UAISimCharacter::applyAttackSpeed(float value)
{
	float newAttackSpeed = value;
	m_NewAttackSpeed = newAttackSpeed;
}

void UAISimCharacter::applyMovementSpeed(float value)
{
	m_MovementSpeed = m_DefaultMovementSpeed * value;
}

uint8 UAISimCharacter::getCondtionCount()
{
	return m_ConditionCount;
}

uint8 UAISimCharacter::getDebuffCount()
{
	return m_DebuffCount;
}

HBCharacterState UAISimCharacter::getState()
{
	return m_State;
}

FWeaponValues UAISimCharacter::getWeapon()
{
	return weapon;
}

SkillType UAISimCharacter::getCurrentSkillType()
{
	return currentSkill.skill->properties.skillType;
}

UAISimCharacter* UAISimCharacter::clone()
{
	UAISimCharacter* character = NewObject<UAISimCharacter>();
	character->m_Health = m_Health;
	character->m_MaxHealth = m_MaxHealth;

	return character;
}

void UAISimCharacter::knockDownCharacter(float duration)
{

}

void UAISimCharacter::Remove(RemoveType type, int count)
{
	switch (type)
	{
	case RemoveType::CONDI:
		break;
	case  RemoveType::HEX:
		break;
	case RemoveType::ENTCHANTMENT:
		break;
	case RemoveType::STANCE:
		break;
	default:
		break;
	}
}

void UAISimCharacter::setCoolDown(float time, CoolDownType cdType)
{

	switch (cdType)
	{
	case CoolDownType::ALL:
		setCoolDownAll(time);
		break;
	case CoolDownType::ATTRIBUTE:
		setAttributeCoolDown(time);
		break;
	case CoolDownType::CURRENTSKILL:
		setCurrentSkillCoolDown(time);
		break;
	case CoolDownType::INTERRUPT:
		setInterruptCoolDown(time);
		break;
	default:
		break;
	}

}

void UAISimCharacter::setState(HBCharacterState state, UAISimCharacter* target)
{
	m_State = state;
	selectedTarget = target;
}

void UAISimCharacter::updateHealthRegen(float regen)
{
	m_HealthRegeneration += regen;
}

void UAISimCharacter::UpdateAdrenaline()
{
	for (auto& adrenaline : m_AdrenalineList)
	{
		if (adrenaline.currentAdrenaline < adrenaline.maxAdrenaline)
		{
			adrenaline.currentAdrenaline++;
		}
	}
}

void UAISimCharacter::UpdateModifier()
{
	if (m_AttackSpeed != m_AttackSpeed)
		m_AttackSpeed = m_NewAttackSpeed;
	/*if (m_DefaultMovementSpeed != m_MovementSpeed)
		GetCharacterMovement()->MaxWalkSpeed = m_MovementSpeed;
	else
		GetCharacterMovement()->MaxWalkSpeed = m_DefaultMovementSpeed;*/

	m_NewAttackSpeed = weapon.attackSpeed;
	m_MovementSpeed = m_DefaultMovementSpeed;
}

bool UAISimCharacter::RunBuff(Trigger trigger, UAISimCharacter* caster, int value /*= 0*/)
{
	bool b = true;
	if (m_CompleteBuffList.Contains(trigger))
	{
		TMap<FString, UBuff*> buffList = m_CompleteBuffList.Find(trigger)->m_BuffList;
		for (auto& buff : buffList)
		{
			b = b && buff.Value->runSim(caster, this, value);
		}
	}
	return b;
}
