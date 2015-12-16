#include "Herobattle.h"
#include "ScHeal.h"
#include "../../Base/BaseCharacter.h"
#include "AI/SkillScore.h"

UScHeal::UScHeal()
{
	componentName = TEXT("Heal");
}


UScHeal::~UScHeal()
{
}


bool UScHeal::run(ABaseCharacter* target, ABaseCharacter* self, FString SkillName /*= TEXT("Name")*/)
{
	ABaseCharacter* testTarget;
	if (targetType == ComponentTarget::SELF)
		testTarget = self;
	else
		testTarget = target;

	float heal = scaleTable[self->getAttributeValue(scaleAttribute)];
	testTarget->heal(self, heal);
	return true;
}
float UScHeal::getScore(ABaseCharacter* caster, FCharacterState characterState, USkillScore* skillScore)
{
	
	float heal = scaleTable[caster->getAttributeValue(scaleAttribute)];
	skillScore->addHeal(heal, targetType);
	return 0.0f;
}

void UScHeal::init(FXmlNode* node)
{
	targetType = SkillEnums::stringToComponentTarget(node->GetAttribute("target"));
	FString tagName = node->GetTag();
	if (tagName.Equals(TEXT("heal")))
	{
		fillScaleTable(node);
	}
}

FString UScHeal::ToString()
{
	FString sCText = componentName;
	sCText.Append(TEXT(" \n "));
	sCText.Append(Super::ToString());

	return sCText;
}
