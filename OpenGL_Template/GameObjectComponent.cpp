//GameObjectComponent.cpp

#include "GameObjectComponent.h"

GameObjectComponent::GameObjectComponent(const ComponentID id, GameObject* pGameObject)
    :m_componentID(id)
    , m_pGameObject(pGameObject)
{
    //
}