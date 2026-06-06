#include "ExperienceComponent.h"

#include "GameObject.h"
#include "ExpOrbComponent.h"

void ExperienceComponent::Start()
{

}

void ExperienceComponent::Update(float deltaTime)
{

}

void ExperienceComponent::Render()
{

}

void ExperienceComponent::OnCollisionEnter(Collider* collider)
{
    if (collider->Owner()->GetComponent<ExpOrbComponent>())
        AddExp(collider->Owner()->GetComponent<ExpOrbComponent>()->GetExpValue());
}

void ExperienceComponent::AddExp(int value)
{
    this->currentExp += value;
    if (currentExp >= nextLevelExp) {
        level += 1;     //等级加一
        currentExp -= nextLevelExp;
        nextLevelExp *= 2;
        //TODO:需要一个数组记录每一个等级需要的经验值
    }
}

float ExperienceComponent::GetExpPercent() const
{
    float currExp = static_cast<float>(currentExp);
    float nextExp = static_cast<float>(nextLevelExp);
    return static_cast<float>(currExp / nextExp);
}

int ExperienceComponent::GetLevel() const
{
    return level;
}
