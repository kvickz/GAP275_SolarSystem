//GameObjectFactory.cpp

#include "GameObjectFactory.h"

#include "GameObjectComponentFactory.h"

GameObject* GameObjectFactory::CreatePlanet(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_planetID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Render Component
    RenderComponent* pRenderComponent = componentFactory.CreateRenderComponent(pObject, pTransform);
    pObject->AddComponent(k_renderComponentID, pRenderComponent);

    return pObject;
}

GameObject* GameObjectFactory::CreateCamera(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_cameraID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Camera Component
    CameraComponent* pCameraComponent = componentFactory.CreateCameraComponent(pObject, pTransform);
    pObject->AddComponent(k_cameraComponentID, pCameraComponent);

    return pObject;
}