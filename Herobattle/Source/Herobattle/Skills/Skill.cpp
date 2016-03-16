// Fill out your copyright notice in the Description page of Project Settings.

#include "Herobattle.h"
#include "Engine.h"
#include "Skill.h"
#include "Components/BaseSkillComponent.h"
#include "Base/BaseCharacter.h"
#include "UnrealNetwork.h"
#include "SkillMessages.h"
#include "AI/SkillScore.h"
#include "AI/AISimCharacter.h"
#include "../ImageWrapper/Public/Interfaces/IImageWrapperModule.h"



USkill::USkill()
{
	name = TEXT("default");
}

USkill::~USkill()
{
}

bool USkill::run(ABaseCharacter* target, ABaseCharacter* self)
{
	bool b = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, name);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(properties.cost));
	for (auto& sc : componentList)
	{
		b = sc->run(target, self, name);
	}

	return b;
}

bool USkill::runSim(UAISimCharacter* target, UAISimCharacter* self)
{
	bool b = true;
	for (auto& sc : componentList)
	{
		b = sc->runSim(target, self, name);
	}

	return b;
}

bool USkill::isValidTarget(ABaseCharacter* target, ABaseCharacter* self)
{
	if (target->getState() == HBCharacterState::DEATH)
		return false;
	else if (target->isEnemy(self->ETeam) && properties.targetType == TargetType::ENEMY)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && properties.targetType == TargetType::SELFFRIEND)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && properties.targetType == TargetType::FRIEND && target != self)
	{
		return true;
	}
	else if (target == self && properties.targetType == TargetType::SELF)
	{
		return true;
	}
	else
	{
		self->messages->registerMessage(TEXT("Invalide Target"), MessageType::SKILLERROR);
		return false;
	}
}

bool USkill::isValidTargetSim(UAISimCharacter* target, UAISimCharacter* self)
{
	if (target->isEnemy(self->ETeam) && properties.targetType == TargetType::ENEMY)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && properties.targetType == TargetType::SELFFRIEND)
	{
		return true;
	}
	else if (!(target->isEnemy(self->ETeam)) && properties.targetType == TargetType::FRIEND && target != self)
	{
		return true;
	}
	else if (target == self && properties.targetType == TargetType::SELF)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool USkill::isInRange(ABaseCharacter* target, ABaseCharacter* self)
{
	FVector location = self->GetActorLocation();
	float airDistance = (location - target->GetActorLocation()).Size();
	if (properties.targetType == TargetType::SELF)
	{
		return true;
	}
	else if (properties.range > airDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float USkill::getScore(ABaseCharacter* caster, FCharacterState charcterState)
{

	USkillScore* skillScore = NewObject<USkillScore>();
	for (auto& component : componentList)
	{
		component->getScore(caster, charcterState, skillScore);
	}
	ABaseCharacter* target = charcterState.self;
	skillScore->calcDamageScore(caster->m_Health, caster->m_MaxHealth, target->m_Health, target->m_MaxHealth);
	skillScore->calcHealScore(caster->m_Health, caster->m_MaxHealth, target->m_Health, target->m_MaxHealth);
	float score = skillScore->calcCompleteScore() *  manaScore(caster, charcterState);
	return score;

}

float USkill::getScoreSim(UAISimCharacter* caster, FCharacterState characterState)
{
	
	USkillScore* skillScore = NewObject<USkillScore>();
	
	UAISimCharacter* self = NewObject<UAISimCharacter>(this);
	self->init(characterState);
	characterState.selfSim = self;

	for (auto& component : componentList)
	{
		component->getScoreSim(caster, characterState, skillScore);
	}
	UAISimCharacter* target = characterState.selfSim;
	skillScore->calcDamageScore(caster->m_Health, caster->m_MaxHealth, target->m_Health, target->m_MaxHealth);
	skillScore->calcHealScore(caster->m_Health, caster->m_MaxHealth, target->m_Health, target->m_MaxHealth);
	float score = skillScore->calcCompleteScore() *  ((manaScoreSim(caster, characterState) + skillScore->DurationScore())/2);
	return score;
}

FString USkill::ToString()
{
	FString skillText = name;
	for (auto& sc : componentList)
	{
		skillText.Append(TEXT("\n"));
		skillText.Append(TEXT("\t"));
		skillText.Append(sc->ToString());
	}
	return skillText;
}

UTexture2D* USkill::getImage()
{
	UTexture2D* Texture = nullptr;

	FString projectDir = FPaths::GameDir();
	FString FileName = name.Replace(TEXT(" "), TEXT("_")) + TEXT(".jpg");
	FString TexturePath = projectDir + TEXT("/Content/SkillImages/") + FileName;

	// Represents the entire file in memory.
	TArray<uint8> RawFileData;

	if (FFileHelper::LoadFileToArray(RawFileData, *TexturePath))
	{
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
		IImageWrapperPtr ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

		if (FFileHelper::LoadFileToArray(RawFileData, *TexturePath))
		{
			if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
			{
				const TArray<uint8>* UncompressedBGRA = nullptr;
				if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
				{
					Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);

					// Fill in the source data from the file
					void* TextureData = Texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
					FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
					Texture->PlatformData->Mips[0].BulkData.Unlock();
					Texture->UpdateResource();
				}
			}
		}
	}

	return Texture;
}

float USkill::manaScore(ABaseCharacter* caster, FCharacterState charcterState)
{
	if (properties.costType == CostType::ADRENALINE || properties.costType == CostType::NONE)
		return 1;
	

	float currentMana = caster->m_Mana;
	float maxMana = caster->m_MaxMana;
	int regen = caster->m_ManaRegeneration;

	int mana_cost = properties.cost - caster->m_ManaReduction;
	if (mana_cost < 0)
		mana_cost = 0;
	float score =  (1 - properties.cost / currentMana) * (regen / 4.0);
	return score;
}

float USkill::manaScoreSim(UAISimCharacter* caster, FCharacterState charcterState)
{
	if (properties.costType == CostType::ADRENALINE && (properties.skillType == SkillType::ATTACK || properties.skillType == SkillType::RANGEATTACK))
		return 1;
	else if (properties.costType == CostType::ADRENALINE)
		return 0.5;
	if (properties.costType == CostType::NONE)
		return 1;
	float currentMana = caster->m_Mana;
	float maxMana = caster->m_MaxMana;
	int regen = caster->m_ManaRegeneration;

	int mana_cost = properties.cost - caster->m_ManaReduction;
	if (mana_cost < 0)
		mana_cost = 0;
	float score = (1 - properties.cost / currentMana) * (regen / 4.0);
	return score;
}

void USkill::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USkill, componentList);
}
