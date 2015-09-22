// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

enum SkillType {ENTCHANTMENT, ATTACK, HEX, SPELL, HEAL};
enum TargetType {SELF, ENEMY, FRIEND, SELFFREND};
// Damage 

class HEROBATTLE_API Skill
{
public:
	Skill();
	~Skill();

private:
	float castTime;
	float recharge;
	int manaCost;

};
