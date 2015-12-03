//TransformComponent.cpp

#include "TransformComponent.h"

#include <SDL.h>
#include <math.h>

TransformComponent::TransformComponent(ComponentID id, GameObject* pGameObject)
    :GameObjectComponent(id, pGameObject, this)
{
    m_position.Zero();
    m_eulerRotation.Zero();
    m_scale.Identity();
}

TransformComponent::~TransformComponent()
{
    //
}

void TransformComponent::Update()
{
    /*float sinVal = sinf(SDL_GetTicks() * 0.0001f) + m_position.x;

    m_position.x += sinVal * 0.01f;*/

    //m_eulerRotation.y += 0.01f;
    //m_eulerRotation.z += 0.01f;

    const float k_factor = 0.04f;
    Scale(k_factor, k_factor, k_factor);
}

//POSITION
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

//ROTATION
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

//SCALE
void TransformComponent::SetScale(float x, float y, float z)
{
    m_scale.x = x;
    m_scale.y = y;
    m_scale.z = z;
}

void TransformComponent::Scale(float x, float y, float z)
{
    m_scale.x += x;
    m_scale.y += y;
    m_scale.z += z;
}