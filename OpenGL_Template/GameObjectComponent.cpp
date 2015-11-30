//GameObjectComponent.cpp

#include "GameObjectComponent.h"

GameObjectComponent::GameObjectComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform)
    :m_componentID(id)
    , m_pGameObject(pGameObject)
    , m_pTransform(pTransform)
{
    //
}