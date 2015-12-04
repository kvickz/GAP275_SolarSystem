//TransformComponent.cpp

#include "TransformComponent.h"

#include <SDL.h>
#include <math.h>

TransformComponent::TransformComponent(ComponentID id, GameObject* pGameObject)
    :GameObjectComponent(id, pGameObject, this)
    , m_pParent(nullptr)
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

    //const float k_factor = 0.04f;
    //Scale(k_factor, k_factor, k_factor);
}

//***************************************************************************************
// Parenting functions
//***************************************************************************************
void TransformComponent::SetParent(TransformComponent* pTransform)
{
    //Can't set transform as parent to itself
    if (pTransform == this)
        return;

    m_pParent = pTransform;
}

void TransformComponent::AddChild(TransformComponent* pTransform)
{
    m_children.push_back(pTransform);
    pTransform->SetParent(this);
}

TransformComponent* TransformComponent::GetChild(const unsigned int index)
{
    return m_children[index];
}

//***************************************************************************************
// POSITION
//***************************************************************************************
//-------------------------------------------------------------------------------------- -
Vector3 TransformComponent::GetWorldPosition()
{
    //If no parent, just return this position
    if (!m_pParent)
        return m_position;

    Vector3 worldPos;
    Vector3 parentWorldPos = m_pParent->GetWorldPosition();
    worldPos.x = parentWorldPos.x + m_position.x;
    worldPos.y = parentWorldPos.y + m_position.y;
    worldPos.z = parentWorldPos.z + m_position.z;

    return worldPos;
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

//***************************************************************************************
// ROTATION
//***************************************************************************************
//-------------------------------------------------------------------------------------- -
// Get World Rotation Function
//      -Pseudo-recursive function that will grab it's child's position and
//       add it to the local position.
//      -This will recursively grab this parent's transform until there is no parent.
//-------------------------------------------------------------------------------------- -
Vector3 TransformComponent::GetWorldRotation()
{
    //If no parent, just return this position
    if (!m_pParent)
        return m_position;

    Vector3 worldRot;
    Vector3 parentWorldRot = m_pParent->GetWorldRotation();
    worldRot.x = parentWorldRot.x + m_eulerRotation.x;
    worldRot.y = parentWorldRot.y + m_eulerRotation.y;
    worldRot.z = parentWorldRot.z + m_eulerRotation.z;

    return worldRot;
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

//***************************************************************************************
// SCALE
//***************************************************************************************
//-------------------------------------------------------------------------------------- -
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