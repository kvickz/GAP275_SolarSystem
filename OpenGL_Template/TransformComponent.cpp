//TransformComponent.cpp

#include "TransformComponent.h"

#include <SDL.h>
#include <math.h>

TransformComponent::TransformComponent(ComponentID id, GameObject* pGameObject)
    :GameObjectComponent(id, pGameObject)
{
    m_position.x = 0;
    m_position.y = 0;
    m_position.z = 0;

    m_eulerRotation.x = 0;
    m_eulerRotation.y = 0;
    m_eulerRotation.z = 0;
}

TransformComponent::~TransformComponent()
{
    //
}

void TransformComponent::Update()
{
    /*float sinVal = sinf(SDL_GetTicks() * 0.0001f) + m_position.x;

    m_position.x += sinVal * 0.01f;*/
}

void TransformComponent::SetPosition(float x, float y, float z)
{
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}

void TransformComponent::Translate(float x, float y, float z)
{
    m_position.x += x;
    m_position.y += y;
    m_position.z += z;
}

void TransformComponent::SetEulerRotation(float x, float y, float z)
{
    m_eulerRotation.x = x;
    m_eulerRotation.y = y;
    m_eulerRotation.z = z;
}

void TransformComponent::Rotate(float x, float y, float z)
{
    m_eulerRotation.x += x;
    m_eulerRotation.y += y;
    m_eulerRotation.z += z;
}