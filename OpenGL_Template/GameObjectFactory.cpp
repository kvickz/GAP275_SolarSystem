//GameObjectFactory.cpp

#include "GameObjectFactory.h"

#include "GameObjectComponentFactory.h"

GameObject* GameObjectFactory::CreatePlanet(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_planetID, pGame);

    //Add Transform Component
    pObject->AddComponent(k_transformComponentID, componentFactory.CreateTransformComponent(pObject));

    //Add Render Component
    pObject->AddComponent(k_renderComponentID, componentFactory.CreateRenderComponent(pObject));

    return pObject;
}

GameObject* GameObjectFactory::CreateCamera(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_planetID, pGame);

    //Add Transform Component
    pObject->AddComponent(k_transformComponentID, componentFactory.CreateTransformComponent(pObject));

    //Add Camera Component
    pObject->AddComponent(k_renderComponentID, componentFactory.CreateCameraComponent(pObject));

    return pObject;
}