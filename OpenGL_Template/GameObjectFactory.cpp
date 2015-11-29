//GameObjectFactory.cpp

#include "GameObjectFactory.h"

#include "GameObjectComponentFactory.h"

GameObject* GameObjectFactory::CreatePlanet()
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_planetID);

    //Add Transform Component
    pObject->AddComponent(k_transformComponentID, componentFactory.CreateTransformComponent());

    //Add Render Component
    pObject->AddComponent(k_renderComponentID, componentFactory.CreateTransformComponent());

    return pObject;
}