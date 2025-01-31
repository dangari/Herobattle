// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "BaseCharacter.h"
#include "../Skills/Buff/Buff.h"
#include "../Skills/Condition/BaseCondition.h"
#include "UnrealNetwork.h"
#include "HerobattleGameMode.h"
#include "SkillMessages.h"
#include "Engine.h"
#include "Skills/XMLSkillReader.h"
#include "AI/AISimCharacter.h"
#include "LoadImages.h"

ABaseCharacter::ABaseCharacter()
:m_MaxHealth(600),
m_MaxMana(25),
m_Health(600),
m_Mana(25),
m_HealthRegeneration(0),
m_ManaRegeneration(4),
m_ConditionCount(0),
m_BuffCount(0),
m_DebuffCount(0),
m_HealthBuffRegneration(0),
m_ManaBuffRegneration(0),
m_ManaReduction(0),
m_DamageReduction(0),
m_NewAttackSpeed(1)
{
	bReplicates = true;
	currentSkill.castingSkill = false;
	skillcooldowns.AddDefaulted(8);
	m_AdrenalineList.AddDefaulted(8);
	skillNames.AddDefaulted(8);
}

ABaseCharacter::~ABaseCharacter()
{
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{

	Super::BeginPlay();
	m_SimCharacter = NewObject<UAISimCharacter>(this);
	m_SimCharacterTarget = NewObject<UAISimCharacter>(this);
	
	if (HasAuthority())
	{
		InitializeSkills();
		m_DefaultMovementSpeed = GetCharacterMovement()->MaxWalkSpeed;
		InitializeAdrenaline();
		messages = NewObject<USkillMessages>();
		weapon = FWeaponValues(Weapon::STAFF);
		m_leftAttackTime = weapon.attackSpeed;
		m_AttackSpeed = weapon.attackSpeed;
		currentSkill.castingSkill = false;

		attrList.Add(Attributes::FIRE_MAGIC, 14);
		attrList.Add(Attributes::HEALING_PRAYERS, 14);
		attrList.Add(Attributes::ENERGY_STORAGE, 10);
		attrList.Add(Attributes::EARTH_PRAYERS, 8);
		attrList.Add(Attributes::PROTECTION_PRAYERS, 10);
		attrList.Add(Attributes::TACTICS, 8);
		attrList.Add(Attributes::STRENGTH, 14);
		attrList.Add(Attributes::SPEAR_MASTERY, 12);
	}
	else
	{
		currentSkill.castingSkill = false;
		finishedLoadingSkills();
	}

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	if (HasAuthority())
	{
		Update(DeltaTime);

	}

}

void ABaseCharacter::Update(float DeltaTime)
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

void ABaseCharacter::Death()
{
	m_State = HBCharacterState::DEATH;
	stopCurrentSkill();
	m_leftAttackTime = m_AttackSpeed;
	emptyConditionList();
	emptyBuffList();
	emptyDebuffList();
	AHerobattleGameMode* gameMode = Cast<AHerobattleGameMode>(GetWorld()->GetAuthGameMode());
	gameMode->addDeathCharacter(this);
	m_Health = 0;
	m_Mana = 0;
}

void ABaseCharacter::Respawn()
{
	m_Health = m_MaxHealth;
	m_Mana = m_MaxMana;
	m_State = HBCharacterState::IDLE;
}

void ABaseCharacter::emptyConditionList()
{
	m_ConditionCount = 0;
	m_condtionList.Empty();
}

void ABaseCharacter::emptyBuffList()
{
	m_BuffCount = 0;
	m_BuffList.Empty();
	m_CompleteBuffList.Empty();
}

void ABaseCharacter::emptyDebuffList()
{
	m_DebuffCount = 0;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABaseCharacter::stopCurrentSkill_Implementation()
{
	if (isCastingSkill())
	{
		currentSkill.castingSkill = false;
		m_State = HBCharacterState::IDLE;
	}
}
bool ABaseCharacter::stopCurrentSkill_Validate()
{
	return true;
}



void ABaseCharacter::InitializeAdrenaline()
{
	int i = 0;
	for (auto& skill : skillList)
	{
		if (skill->properties.costType == CostType::ADRENALINE)
		{
			m_AdrenalineList[i].maxAdrenaline = skill->properties.cost;
		}
		else
		{
			m_AdrenalineList[i].maxAdrenaline = 0;
		}
		i++;
	}
}

void ABaseCharacter::InitializeSkills()
{
	XMLSkillReader* skillReader = new XMLSkillReader();
	FString fileName = TEXT("/Content/Definitions/Warrior.xml");
	switch (profession)
	{
	case ProfessionName::NONE:
		break;
	case ProfessionName::ASSASINE:
		break;
	case ProfessionName::ELEMENTALIST:
		fileName = TEXT("/Content/Definitions/EleHero.xml");
		m_MaxHealth = 600;
		m_MaxMana = 75;
		m_Mana = 75;
		m_Health = 600;
		m_ManaRegeneration = 4;
		break;
	case ProfessionName::MONK:
		fileName = TEXT("/Content/Definitions/Monk.xml");
		m_MaxHealth = 600;
		m_MaxMana = 40;
		m_Mana = 40;
		m_Health = 600;
		m_ManaRegeneration = 4;
		break;
	case ProfessionName::DERWISH:
		break;
	case ProfessionName::NEKROMANT:
		break;
	case ProfessionName::PARAGON:
		break;
	case ProfessionName::WARRIOR:
		fileName = TEXT("/Content/Definitions/Warrior.xml");
		m_MaxHealth = 630;
		m_MaxMana = 22;
		m_Mana = 22;
		m_Health = 630;
		m_ManaRegeneration = 2;
		break;
	case ProfessionName::MESMER:
		break;
	case ProfessionName::RITUALIST:
		break;
	default:
		break;
	}
	TArray<USkill*> curSkillList = skillReader->ReadXmlSkillFile(fileName, this);
	if (curSkillList.Num() > 7)
	{
		skillList.Empty();
		skillList.Add(curSkillList[0]);
		skillNames[0] = curSkillList[0]->name;
		skillList.Add(curSkillList[1]);
		skillNames[1] = curSkillList[1]->name;
		skillList.Add(curSkillList[2]);
		skillNames[2] = curSkillList[2]->name;
		skillList.Add(curSkillList[3]);
		skillNames[3] = curSkillList[3]->name;
		skillList.Add(curSkillList[4]);
		skillNames[4] = curSkillList[4]->name;
		skillList.Add(curSkillList[5]);
		skillNames[5] = curSkillList[5]->name;
		skillList.Add(curSkillList[6]);
		skillNames[6] = curSkillList[6]->name;
		skillList.Add(curSkillList[7]);
		skillNames[7] = curSkillList[7]->name;
	}
	
}

void ABaseCharacter::UpdateResources(float DeltaSeconds){


	if (m_State != HBCharacterState::DEATH)
	{
		m_Health += DeltaSeconds * ((m_HealthRegeneration) * 2.0f);
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
		{
			Death();
		}
	}
	m_HealthBuffRegneration = 0;
}


void ABaseCharacter::UpdateCondtion(float DeltaTime)
{
	for (auto& condi : m_condtionList)
	{
		condi.Value->duration -= DeltaTime;
		if (condi.Value->duration <= 0)
		{
			m_condtionList.Remove(condi.Key);
			m_ConditionOrder.Remove(condi.Key);
			m_ConditionCount--;
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

bool ABaseCharacter::skillCost(int slot)
{
	CostType type = skillList[slot]->properties.costType;
	int value = skillList[slot]->properties.cost;
	if (type == CostType::MANA)
	{
		if (((m_Mana + m_ManaReduction) - value) < 0)
		{
			messages->registerMessage(TEXT("Not enough mana"), MessageType::SKILLERROR);
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
			messages->registerMessage(TEXT("Not enough adrenaline"), MessageType::SKILLERROR);
			return false;
		}
	}
	else
	{
		return true;
	}
}




void ABaseCharacter::useAdrenaline(int slot)
{
	m_AdrenalineList[slot].currentAdrenaline = 0;
	for (auto& adrenaline : m_AdrenalineList)
	{
		if (adrenaline.currentAdrenaline > 0)
			adrenaline.currentAdrenaline--;
	}
}

void ABaseCharacter::setCoolDownAll(float Time)
{

}

void ABaseCharacter::setInterruptCoolDown(float Time)
{
	int slot = currentSkill.slot;
	skillcooldowns[slot].currentCooldown = Time;
	skillcooldowns[slot].maxCooldown = Time;
}

void ABaseCharacter::setCurrentSkillCoolDown(float Time)
{
	int slot = currentSkill.slot;
	skillcooldowns[slot].additionalCoolDown = Time;
}

void ABaseCharacter::setAttributeCoolDown(float Time)
{

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

TArray<Condition> ABaseCharacter::getConditions()
{
	TArray<Condition> conditions;
	for (auto& condi : m_condtionList)
	{
		conditions.Add(condi.Key);
	}
	return conditions;
}

float ABaseCharacter::getAirDistance(APawn* pawn)
{
	FVector pawnV = pawn->GetActorLocation();
	FVector characterV = this->GetActorLocation();
	float distance = (pawnV - characterV).Size();
	return distance;
}

float ABaseCharacter::getWalkDistance(APawn* pawn)
{
	return 1.0f;
}

uint8 ABaseCharacter::getBuffCount()
{
	return m_BuffCount;
}

FCharacterProperties ABaseCharacter::getProperties()
{
	FCharacterProperties properties;
	properties.m_Name = m_Name;
	properties.m_MaxHealth = m_MaxHealth;
	properties.m_Health = m_Health;
	properties.m_MaxMana = m_MaxMana;
	properties.m_Mana = m_Mana;
	properties.m_ManaRegeneration = m_ManaRegeneration;
	properties.ETeam = ETeam;
	properties.proffession = profession;
	properties.selectedTarget = selectedTarget;
	properties.simSelectedTarget = nullptr;
	properties.skillList = skillList;

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

	properties.m_CurrentSkill = currentSkill;

	properties.location = GetActorLocation();

	for (int i = 0; i < 8; i++)
	{
		properties.m_AdrenalineList[i] = m_AdrenalineList[i];
		properties.skillcooldowns[i] = skillcooldowns[i];
	}

	return properties;

}

bool ABaseCharacter::isEnemy(TeamColor team)
{
	bool b = team == ETeam;
	return !b;
}

bool ABaseCharacter::hasCondition(Condition condition)
{
	return m_condtionList.Contains(condition);
}

bool ABaseCharacter::canUseSkill(int slot)
{
	if (skillList.Num() > 0)
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
		else if (skillList[slot]->properties.costType == CostType::NONE)
		{
			return true;
		}
	}
	return false;
}

FCharacterState ABaseCharacter::AiExtractor(ABaseCharacter* character)
{
	FCharacterState characterState;
	characterState.ETeam = ETeam;
	characterState.weapon = weapon;
	characterState.location = this->GetActorLocation();
	characterState.airDistance = (characterState.location - character->GetActorLocation()).Size();
	characterState.isCasting = currentSkill.castingSkill;
	characterState.isAutoAttacking = useAutoAttack;
	if (m_BuffCount > 0)
		characterState.isBuffed = true;
	if (m_DebuffCount > 0)
		characterState.isHexed = true;
	characterState.conditions = getConditions();
	characterState.health = m_Health;
	characterState.maxHealth = m_MaxHealth;
	characterState.skillState = currentSkill.copy();
	characterState.selectedTarget = selectedTarget;

	
	characterState.self = this;

	characterState.state = m_State;
	if (m_State == HBCharacterState::CASTING)
		characterState.skillType = currentSkill.skill->properties.skillType;
	else
		characterState.skillType = SkillType::NONE;

	characterState.attrList = attrList;

	characterState.name = m_Name;
	if (selectedTarget)
	{
		characterState.selectedTargetName = selectedTarget->m_Name;
	}
	return characterState;
}

FCharacterState ABaseCharacter::AiExtractorSim(UAISimCharacter* character)
{
	FCharacterState characterState;
	characterState.ETeam = ETeam;
	characterState.weapon = weapon;
	characterState.location = this->GetActorLocation();
	characterState.airDistance = (characterState.location - character->m_location).Size();
	characterState.isCasting = currentSkill.castingSkill;
	characterState.isAutoAttacking = useAutoAttack;
	if (m_BuffCount > 0)
		characterState.isBuffed = true;
	if (m_DebuffCount > 0)
		characterState.isHexed = true;
	characterState.conditions = getConditions();
	characterState.health = m_Health;
	characterState.maxHealth = m_MaxHealth;
	characterState.skillState = currentSkill.copy();
	characterState.selectedTarget = selectedTarget;


	characterState.self = this;
	
	characterState.state = m_State;
	if (m_State == HBCharacterState::CASTING)
		characterState.skillType = currentSkill.skill->properties.skillType;
	else
		characterState.skillType = SkillType::NONE;

	if (selectedTarget)
	{
		characterState.selectedTargetName = selectedTarget->m_Name;
	}

	characterState.attrList = attrList;
	characterState.name = m_Name;
	return characterState;
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

void ABaseCharacter::UpdateCurrentSkill(float deltaTime)
{
	currentSkill.leftCastTime -= deltaTime;
	if (currentSkill.leftCastTime <= 0)
	{
		currentSkill.castingSkill = false;
		skillcooldowns[currentSkill.slot].currentCooldown = currentSkill.skill->properties.recharge;
		skillcooldowns[currentSkill.slot].maxCooldown = currentSkill.skill->properties.recharge + skillcooldowns[currentSkill.slot].additionalCoolDown;
		currentSkill.skill->run(currentSkill.target, this);
		m_ManaReduction = 0;
		RunBuff(Trigger::AFTERCAST, this);
		if (currentSkill.skill->properties.skillType == SkillType::RANGEATTACK || currentSkill.skill->properties.skillType == SkillType::MELEEATTACK)
		{
			UpdateAdrenaline();
			m_State = HBCharacterState::AUTOATTACK;
			RunBuff(Trigger::HIT, this);
		}
		else
		{
			m_State = HBCharacterState::IDLE;
		}
	}
}

void ABaseCharacter::UpdateAttack(float deltaTime)
{
	m_leftAttackTime -= deltaTime;
	if (m_leftAttackTime <= 0)
	{
		int damage = weapon.getDamage();
		selectedTarget->damage(this,damage,HBDamageType::FIRE);
		UpdateAdrenaline();
		m_leftAttackTime = m_AttackSpeed;
		RunBuff(Trigger::HIT, this);
		if (selectedTarget->getState() == HBCharacterState::DEATH)
		{
			changeState(HBCharacterState::IDLE);
		}
	}
}

bool ABaseCharacter::setAttack_Validate(bool b)
{
	return true;
}

void ABaseCharacter::setAttack_Implementation(bool b)
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

bool ABaseCharacter::isAttacking()
{
	if (useAutoAttack && selectedTarget && selectedTarget->isEnemy(ETeam))
	{
		FVector targetLocation = selectedTarget->GetActorLocation();
		FVector myLocation = GetActorLocation();
		float distance = (targetLocation - myLocation).Size();
		UE_LOG(LogTemp, Warning, TEXT("Skill name: %f"), distance);
		if (distance <= weapon.range)
		{
			return true;
		}
		useAutoAttack = false;
		return false;
	}
	useAutoAttack = false;
	return false;
}


void ABaseCharacter::ChangeMana(float value)
{
	if (HasAuthority())
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



struct FSkillHUD ABaseCharacter::getCurrentCast()
{
	FSkillHUD data;
	data.castTime = currentSkill.castTime;
	data.leftCastTime = currentSkill.leftCastTime;
	data.skillName = currentSkill.skillName;
	return data;
}

bool ABaseCharacter::UseSkill(ABaseCharacter* target, int32 slot)
{
	if (HasAuthority() && m_State != HBCharacterState::DEATH)
	{
		USkill* skill = skillList[slot];
		ABaseCharacter* newTarget = target;

		//automatically sets target to self if the skill can be used on self and the target is enemy
		//also sets target to self if targettype is self
		if (skill->properties.castTime <= 0 && skill->properties.targetType == TargetType::SELF && !skillIsOnCooldown(slot) && skillCost(slot))
		{
			skillcooldowns[slot].currentCooldown = skill->properties.recharge;
			skillcooldowns[slot].maxCooldown = skill->properties.recharge + skillcooldowns[currentSkill.slot].additionalCoolDown;
			skill->run(this, this);
			m_ManaReduction = 0;
			return true;
		}
		if (skill->properties.targetType == TargetType::SELF || skill->properties.targetType == TargetType::SELFFRIEND && ((!target || target->isEnemy(ETeam))))
		{
			newTarget = this;
		}

		RunBuff(Trigger::BEFORECAST, this);

		if (newTarget && !skillIsOnCooldown(slot) && !isCastingSkill() && skill->isValidTarget(newTarget, this) && skill->isInRange(newTarget, this) && skillCost(slot))
		{
			currentSkill.registerSkill(skill, newTarget, slot);
			if (skill->properties.skillType == SkillType::MELEEATTACK || skill->properties.skillType == SkillType::RANGEATTACK)
			{
				currentSkill.castTime = m_AttackSpeed;
				currentSkill.leftCastTime = m_AttackSpeed;
			}
			m_State = HBCharacterState::CASTING;
			UE_LOG(LogTemp, Warning, TEXT("Skill name: %s"), *(currentSkill.skillName));
			useAutoAttack = false;
			m_leftAttackTime = m_AttackSpeed;
			//bool b = skill->run(target, this);
			return true;
		}
		
	}
	return false;
}


bool ABaseCharacter::isCastingSkill(FString message)
{
	FString out = TEXT(" ");
	bool b = false;
	if (HasAuthority())
	{
		out = out.Append(message).Append(TEXT(" Server"));
		b = currentSkill.castingSkill;
	}
		
	else
	{
		out = out.Append(message).Append(TEXT(" Client"));
		
		b = currentSkill.castingSkill;
	}
	if (!(message.Equals(TEXT("NOTHING"))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, out);
	}
	return b;
}

FAdrenaline ABaseCharacter::GetCurrentAdrenaline(uint8 slot)
{
	return m_AdrenalineList[slot];
}

bool ABaseCharacter::changeState(HBCharacterState state)
{
	if (HasAuthority())
	{
		if (m_State == HBCharacterState::AUTOATTACK)
		{
			setAttack(false);
			m_leftAttackTime = m_AttackSpeed;
		}
		m_State = state;
		return true;
	}
	return false;
}

HBCharacterState ABaseCharacter::getCurrentState()
{
	return m_State;
}

FString ABaseCharacter::GetSkillName(uint8 slot)
{
	USkill* skill = skillList[slot];
	FString name = TEXT("Dummy");
	if (skill)
	{
		name = skill->name;
		name = name.Replace(TEXT(" "), TEXT("_"));
	}
	return name;
}

UTexture2D* ABaseCharacter::GetSkillImage(uint8 slot)
{
	if (skillList.Num() < 8)
	{
		InitializeSkills();
		InitializeAdrenaline();
	}
	FString skillName = skillNames[slot];
	UTexture2D* image = nullptr;
	if (!skillName.IsEmpty())
	{
		ULoadImages* loader = NewObject<ULoadImages>(this);
		image = loader->LoadSkillImage(skillName);
	}
	return image;
}

float ABaseCharacter::GetAttackSpeed()
{
	return m_AttackSpeed;
}

void ABaseCharacter::switchBuildByProfession(ProfessionName p)
{
	profession = p;
	InitializeSkills();
	InitializeAdrenaline();
}

void ABaseCharacter::DamageSelf(float damage)
{
	if (HasAuthority())
	{
		m_Health -= damage;
	}
}

void ABaseCharacter::finishedLoadingSkills_Implementation()
{

}

void ABaseCharacter::heal(ABaseCharacter* caster, float value, bool withBuff)
{

	if (HasAuthority())
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
}


void ABaseCharacter::damage(ABaseCharacter* caster, float value, HBDamageType damageType, bool withBuff)
{
	if (HasAuthority() && m_State != HBCharacterState::DEATH)
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
		{
			Death();
			return;
		}
		m_DamageReduction = 0;
	}
}

void ABaseCharacter::applyBuff(UBuff* buff, Trigger trigger)
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

void ABaseCharacter::applyDebuff(UBaseSkillComponent* buff)
{

}

void ABaseCharacter::apllyUniQueBuff(UBuff* buff)
{

}

uint8 ABaseCharacter::getAttributeValue(Attributes attributeName)
{
	if (attrList.Contains(attributeName))
		return *(attrList.Find(attributeName));
	else
		return 0;
}

void ABaseCharacter::applyCondition(UBaseCondition* condition)
{
	if (!(m_condtionList.Contains(condition->condition)))
		m_ConditionCount++;
	m_condtionList.Add(condition->condition, condition);
	m_ConditionOrder.AddUnique(condition->condition);
	
}

void ABaseCharacter::applyManaReduction(int value)
{
	if (HasAuthority())
	{
		m_ManaReduction += value;
	}
}

void ABaseCharacter::applyDamageReduction(float value)
{
	if (HasAuthority())
	{
		m_DamageReduction += value;
	}
}

void ABaseCharacter::applyRegneration(int value, RegnerationType type)
{

	if (HasAuthority())
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
}

void ABaseCharacter::applyAttackSpeed(float value)
{
	float newAttackSpeed = value;
	m_NewAttackSpeed = newAttackSpeed;
}

void ABaseCharacter::applyMovementSpeed(float value)
{
	m_MovementSpeed = m_DefaultMovementSpeed * value;
}

float ABaseCharacter::missingAdrenaline()
{
	int count = 0;
	int missing = 0;
	for (int i = 0; i < 8; i++)
	{
		if (m_AdrenalineList[i].maxAdrenaline > 0)
		{
			count++;
			missing += m_AdrenalineList[i].currentAdrenaline - m_AdrenalineList[i].maxAdrenaline;
		}
	}
	return missing / count;
}

void ABaseCharacter::addAdrenaline(int value)
{
	for (int i = 0; i < 8; i++)
	{
		if (skillcooldowns[i].currentCooldown < 0.0001)
		{
			m_AdrenalineList[i].currentAdrenaline += value;
			if (m_AdrenalineList[i].currentAdrenaline > m_AdrenalineList[i].maxAdrenaline)
				m_AdrenalineList[i].currentAdrenaline = m_AdrenalineList[i].maxAdrenaline;
		}
	}
}

uint8 ABaseCharacter::getCondtionCount()
{
	return m_ConditionCount;
}

uint8 ABaseCharacter::getDebuffCount()
{
	return 0;
}

HBCharacterState ABaseCharacter::getState()
{
	return m_State;
}

FWeaponValues ABaseCharacter::getWeapon()
{
	return weapon;
}

SkillType ABaseCharacter::getCurrentSkillType()
{
	return currentSkill.skill->properties.skillType;
}

ABaseCharacter* ABaseCharacter::clone()
{
	ABaseCharacter* character = NewObject<ABaseCharacter>();
	character->m_Health = m_Health;
	character->m_MaxHealth = m_MaxHealth;

	return character;
}

void ABaseCharacter::knockDownCharacter(float duration)
{

}

void ABaseCharacter::Remove(RemoveType type, int count)
{
	switch (type)
	{
	case RemoveType::CONDI:
		if (m_ConditionCount > 0)
		{
			Condition condi = m_ConditionOrder.Last();
			m_condtionList.Remove(condi);
			m_ConditionOrder.Remove(condi);
			m_ConditionCount--;
		}
		
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

void ABaseCharacter::setCoolDown(float time, CoolDownType cdType)
{
	if (HasAuthority())
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
}

void ABaseCharacter::setState(HBCharacterState state, ABaseCharacter* target)
{
	m_State = state;
	selectedTarget = target;
}

void ABaseCharacter::updateHealthRegen(float regen)
{
	m_HealthRegeneration += regen;
}

void ABaseCharacter::UpdateAdrenaline()
{
	for (int i = 0; i < 8; i++)
	{
		if (m_AdrenalineList[i].currentAdrenaline < m_AdrenalineList[i].maxAdrenaline && skillcooldowns[i].currentCooldown < 0.0001)
		{
			m_AdrenalineList[i].currentAdrenaline++;
		}
	}
}

void ABaseCharacter::UpdateModifier()
{
	if (m_AttackSpeed != m_AttackSpeed)
		m_AttackSpeed = m_NewAttackSpeed;
	if (m_DefaultMovementSpeed != m_MovementSpeed)
		GetCharacterMovement()->MaxWalkSpeed = m_MovementSpeed;
	else
		GetCharacterMovement()->MaxWalkSpeed = m_DefaultMovementSpeed;

	m_NewAttackSpeed = weapon.attackSpeed;
	m_MovementSpeed = m_DefaultMovementSpeed;
}

bool ABaseCharacter::RunBuff(Trigger trigger, ABaseCharacter* caster, int value /*= 0*/)
{
	bool b = true;
	if (m_CompleteBuffList.Contains(trigger))
	{
		TMap<FString, UBuff*> buffList = m_CompleteBuffList.Find(trigger)->m_BuffList;
		for (auto& buff : buffList)
		{
			b = b && buff.Value->run(caster, this, value);
		}
	}
	return b;
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter, m_Name);
	DOREPLIFETIME(ABaseCharacter, m_MaxHealth);
	DOREPLIFETIME(ABaseCharacter, m_MaxMana);
	DOREPLIFETIME(ABaseCharacter, m_Health);
	DOREPLIFETIME(ABaseCharacter, m_Mana);
	DOREPLIFETIME(ABaseCharacter, m_ManaRegeneration);
	DOREPLIFETIME(ABaseCharacter, m_HealthRegeneration);
	DOREPLIFETIME(ABaseCharacter, currentSkill);
	DOREPLIFETIME(ABaseCharacter, messages);
	DOREPLIFETIME(ABaseCharacter, selectedTarget);
	DOREPLIFETIME(ABaseCharacter, weapon);
	DOREPLIFETIME(ABaseCharacter, skillcooldowns);
	DOREPLIFETIME(ABaseCharacter, m_AdrenalineList);
	DOREPLIFETIME(ABaseCharacter, m_State);
	DOREPLIFETIME(ABaseCharacter, SpawnPoint);
	DOREPLIFETIME(ABaseCharacter, PositionAtSpawn);
	DOREPLIFETIME(ABaseCharacter, profession);
	DOREPLIFETIME(ABaseCharacter, m_AttackSpeed);
	DOREPLIFETIME(ABaseCharacter, skillNames);
}

