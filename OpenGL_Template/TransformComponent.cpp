//TransformComponent.cpp

#include "TransformComponent.h"

TransformComponent::TransformComponent(ComponentID id)
    :GameObjectComponent(id)
{
    m_position.x = 0;
    m_position.y = 0;
    m_position.z = 0;
}

TransformComponent::~TransformComponent()
{
    //
}

void TransformComponent::Update()
{
    m_position.x += 0.01f;
}