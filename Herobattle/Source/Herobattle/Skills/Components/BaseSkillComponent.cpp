#include "Herobattle.h"
#include "BaseSkillComponent.h"
#include "XmlParser.h"
#include "Engine.h"
#include "../../Base/BaseCharacter.h"


UBaseSkillComponent::UBaseSkillComponent()
{
	
}


UBaseSkillComponent::~UBaseSkillComponent()
{
}


void UBaseSkillComponent::run(ABaseCharacter* target, ABaseCharacter* self)
{

}
float UBaseSkillComponent::getScore()
{
	return 0.f;
}

void UBaseSkillComponent::init(FXmlNode* node)
{

}


